from flask import Flask, render_template, request, jsonify
import requests
app = Flask(__name__)

import redis
r = redis.Redis(host='localhost', port=6379, db=0)

# TODO:
# PUT /<key> – Adds a versioned object
# GET /<key> – Retrieves the latest version of a key
# GET /<key>/<version> – Retrieves a specific version of a key
# DELETE /<key> – Completely deletes a key
