# CS 240 - Final Project (Part 2)
# See: https://courses.engr.illinois.edu/cs240/sp2021/project/week2/

import argparse
from flask import Flask, render_template, request, jsonify
from music21 import stream, note, duration, tempo
import requests

import argparse

parser = argparse.ArgumentParser(description='Process some integers.')

parser.add_argument('--server', required=True, help='server name')
parser.add_argument('--song', required=True, help='song name to request')

args = parser.parse_args()
server = args.server
song = args.song
baseurl = "http://" + server + "/" + song + "/"


def create_song(base_url):
    notes_list = []
    version = 1
    totalOffset = 0
    hasOffset = False
    while True:
        hasOffset = False
        r = requests.get(base_url + str(version))
        if (r.status_code == 404):
            print(version)
            break
        #process note from json
        value = r.json()['value']
        strValue = value.split()
        pc = strValue[1][1:-2]
        dur = float(strValue[3][:-1])
        n = note.Note(pc)
        n.duration = duration.Duration(dur)
        n.offset = totalOffset
        for i in range(len(strValue)):
            if strValue[i] == '"tempo":':
                i += 1
                t = float(strValue[i][:-1])
                met_mark = tempo.MetronomeMark(number=t)
                met_mark.offset = totalOffset
                notes_list.append(met_mark)
            if strValue[i] == '"offset":':
                i += 1
                n.offset = float(strValue[i][:-1])
                hasOffset = True

        notes_list.append(n)
        if not hasOffset:
            totalOffset += dur
        version += 1
    midi_stream = stream.Stream(notes_list)
    midi_stream.write("midi", fp=song + ".mid")
    
create_song(baseurl)