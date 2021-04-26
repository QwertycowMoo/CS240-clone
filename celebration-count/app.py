from flask import Flask, request, jsonify
app = Flask(__name__)


# PUT /celebration
@app.route('/celebration', methods=["PUT"])
def put_celebration():
  value = request.data.decode("utf-8")  
  return "", 500


# GET /
@app.route('/', methods=["GET"])
def get():
  return "", 500


# GET /count
@app.route('/count', methods=["GET"])
def get_count():
  return "", 500
