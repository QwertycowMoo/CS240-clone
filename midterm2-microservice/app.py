from flask import Flask, request, jsonify
app = Flask(__name__)


# PUT /guest/<guest>
@app.route('/guest/<guest>', methods=["PUT"])
def put_guest(guest):
  return "", 500


# DELETE /guest/<guest>
@app.route('/guest/<guest>', methods=["DELETE"])
def delete_guest(guest):
  return "", 500


# GET /guest/<guest>
@app.route('/guest/<guest>', methods=["GET"])
def get_guest(guest):
  return "", 500
