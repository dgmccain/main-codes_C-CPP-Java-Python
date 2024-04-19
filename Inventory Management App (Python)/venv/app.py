from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///inventory.db'
db = SQLAlchemy(app)

class Item(db.Model):
    name = db.Column(db.String(80), primary_key=True)
    quantity = db.Column(db.Integer)

@app.route('/')
def home():
    inventory = {item.name: item.quantity for item in Item.query.all()}
    return render_template('index.html', inventory=inventory)

@app.route('/add', methods=['POST'])
def add():
    name = request.form.get('name')
    quantity = request.form.get('quantity')
    item = Item.query.get(name)
    if item is None:
        item = Item(name=name, quantity=quantity)
        db.session.add(item)
    else:
        item.quantity = quantity
    db.session.commit()
    return redirect(url_for('home'))

@app.route('/edit', methods=['GET', 'POST'])
def edit():
    if request.method == 'POST':
        name = request.form.get('name')
        quantity = request.form.get('quantity')
        item = Item.query.get(name)
        if item is not None:
            item.quantity = quantity
            db.session.commit()
        return redirect(url_for('home'))
    else:
        inventory = {item.name: item.quantity for item in Item.query.all()}
        return render_template('edit.html', inventory=inventory)


@app.route('/remove', methods=['GET', 'POST'])
def remove():
    if request.method == 'POST':
        name = request.form.get('name')
        item = Item.query.get(name)
        if item is not None:
            db.session.delete(item)
            db.session.commit()
        return redirect(url_for('home'))
    else:
        inventory = {item.name: item.quantity for item in Item.query.all()}
        return render_template('remove.html', inventory=inventory)

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
    app.run(debug=True)
