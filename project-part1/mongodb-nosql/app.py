from flask import Flask, render_template, request, jsonify
import requests
app = Flask(__name__)


from pymongo import MongoClient
mongo = client = MongoClient('localhost', 27017)
db = mongo["state-server"]


# TODO:
# PUT /<key> – Adds a versioned object
# GET /<key> – Retrieves the latest version of a key
# GET /<key>/<version> – Retrieves a specific version of a key
# DELETE /<key> – Completely deletes a key
