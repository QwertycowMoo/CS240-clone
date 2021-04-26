from flask import Flask, render_template, request, jsonify
import requests
app = Flask(__name__)


from pymongo import MongoClient
mongo = client = MongoClient('localhost', 27017)
db = mongo["state-server"]

@app.route('/<key>', methods=['PUT', 'DELETE', 'GET'])
def key(key):
    keys = db.keys
    if request.method == 'PUT':
        
        if (keys.find_one_and_update({"key":key}, {'$push':{"values": request.data.decode('utf-8')}}) == None):
            keys.insert_one({"key": key, "values": [request.data.decode('utf-8')]})
            print("new document: ", keys.find_one({"key": key}))
        return "Success", 200
    elif request.method == 'DELETE':
        keys.delete_one({"key":key})
        return "Success", 200
    elif request.method == 'GET':
        doc = keys.find_one({"key": key})
        if(doc == None):
            return "Not found!", 404
        values = doc["values"]
        value = values[-1]
        result = {
            "value": value,
            "version": len(values)
            }
        return jsonify(result), 200

@app.route('/<key>/<version>', methods=['GET'])
def getVersion(key, version):
    keys = db.keys
    print("inside GET version")
    
    doc = keys.find_one({"key": key})
    print(key, version)
    if (doc != None):
        values = doc["values"]
        if (int(version) <= len(values)):
            value = values[int(version) - 1]
            result = {
                "value": value,
                "version": int(version)
                }
            return jsonify(result), 200
        else:
            return "Not found!", 404
    else: 
        return "Not found!", 404

# TODO:
# PUT /<key> – Adds a versioned object
# GET /<key> – Retrieves the latest version of a key
# GET /<key>/<version> – Retrieves a specific version of a key
# DELETE /<key> – Completely deletes a key
