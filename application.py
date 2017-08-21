from flask import Flask, flash, redirect, render_template, request, session, url_for

# configure application
app = Flask(__name__)


@app.route("/")
def index():
    return render_template("play.html")
# intended to have an actual homepage but there is not much use for it with current implementation.

@app.route("/game")
def game():
    return render_template("play.html")

@app.route("/testclick")
def testclick():
    return render_template("testclick.html")


@app.route("/about")
def about():
    return render_template("about.html")
