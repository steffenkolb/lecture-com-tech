from flask import Flask
from flask_restful import Api, Resource, reqparse
import datetime
import logging

log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

app = Flask(__name__)
api = Api(app)
parser = reqparse.RequestParser()
parser.add_argument('message')

class HelloWorld(Resource):
    def get(self):
        return "Hello World!";

    def post(self):
        now = str(datetime.datetime.now())
        args = parser.parse_args()
        message =  args['message']
        print(now + ": " + message)
        return 200


api.add_resource(HelloWorld, '/')

if __name__ == '__main__':
    app.run(debug=True)