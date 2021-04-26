from flask import Flask, render_template, request, jsonify
import requests
app = Flask(__name__)

import redis
r = redis.Redis(host='localhost', port=6379, db=0)


@app.route('/<key>', methods=['PUT', 'DELETE', 'GET'])
def key(key):
    if request.method == 'PUT':
        #so each key will get its own list, then we can grab from that list
        r.rpush(key, request.data.decode('utf-8'))
        print(r.lindex(key, -1))
        return "Success", 200
    elif request.method == 'DELETE':
        r.delete(key)
        return "Success", 200
    elif request.method == 'GET':
        #key is a strings
        if (r.exists(key)):  
            print("GET", r.lindex(key, -1).decode())
            result = {
                "value": r.lindex(key, -1).decode(),
                "version": r.llen(key)
                }
            print(result)
            return jsonify(result), 200
        else:
            return "Not found!", 404

@app.route('/<key>/<version>', methods=['GET'])
def getVersion(key, version):
    if (r.exists(key)): 
        if (int(version) <= r.llen(key)): 
            result = {
                "value": r.lindex(key, int(version) - 1).decode(),
                "version": int(version)
                }
            return jsonify(result), 200
    return "Not found!", 404
# TODO:
# PUT /<key> – Adds a versioned object
# GET /<key> – Retrieves the latest version of a key
# GET /<key>/<version> – Retrieves a specific version of a key
# DELETE /<key> – Completely deletes a key
