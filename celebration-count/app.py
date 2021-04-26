from flask import Flask, request, jsonify
app = Flask(__name__)

celebrations = []
# PUT /celebration
@app.route('/celebration', methods=["PUT"])
def put_celebration():
  value = request.data.decode("utf-8")
  celebrations.append(value)
  return "Success", 200


# GET /
@app.route('/', methods=["GET"])
def get():
  result = {"celebrations": celebrations}
  return jsonify(result), 200


# GET /count
@app.route('/count', methods=["GET"])
def get_count():
  result = {"count": len(celebrations)}
  return jsonify(result), 200
