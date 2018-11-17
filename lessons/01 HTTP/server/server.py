from flask import Flask, request
import datetime

app = Flask(__name__)

@app.route("/",  methods=["GET"])
def get_helloWorld():
    return "Hello World!";

@app.route("/",  methods=["POST"])
def post():
    now = str(datetime.datetime.now())
    message =  request.data
    if(message is not None):
        print(now + ": " + message)
    return "Nice!"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)