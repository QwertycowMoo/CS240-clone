from flask import Flask, render_template, request, jsonify
import requests, sqlite3
app = Flask(__name__)

conn = sqlite3.connect('stateServer.db')
# TODO:
# PUT /<key> – Adds a versioned object
# GET /<key> – Retrieves the latest version of a key
# GET /<key>/<version> – Retrieves a specific version of a key
# DELETE /<key> – Completely deletes a key
