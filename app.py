from flask import Flask, render_template,flash,redirect,url_for,session,request,logging      # render_template : 요청한 클라이언트에 HTML형식으로 문서화 시켜서 보내는 Class
from passlib.hash import pbkdf2_sha256
import pymysql
from functools import wraps
import plot
app = Flask(__name__)
app.debug=True

db = pymysql.connect(host = 'localhost', port = 3306, user = 'root', passwd='1234',db = 'myflaskapp')
cursor = db.cursor()

def is_logged_out(f):
    @wraps(f)
    def wrap(*args,**kwargs):
        if 'is_logged' in session:
            return redirect(url_for('login'))
        else:
            return f(*args , **kwargs)
    return wrap

def is_logged_in(f):
    @wraps(f)
    def _wraper(*args, **kwargs):
        if 'is_logged' in session:
        # if session['is_logged']:
            print("logged in")
            return f(*args,**kwargs)
        else :
            flash('UnAuthorized,Please login','danger')
            print("not logged in")
            return redirect(url_for('login'))

    return _wraper

@app.route('/index')
def index():
    print("Success")
    # return "TEST"
    return render_template('index.html')


@app.route('/')
def home():
    print("Success")
    # return "TEST"
    return redirect('/index')



@app.route("/register",methods=['GET','Post'])
@is_logged_out
def register():
    if request.method == 'POST':
        # data = request.body.get('author')
        email = request.form.get('email')
        password = pbkdf2_sha256.hash(request.form.get('password'))
        re_password = request.form.get('re_password')
        sql = 'SELECT email FROM users WHERE email = %s'
        cursor.execute(sql,[email])
        username_1 = cursor.fetchone()
        if  username_1:
            return redirect(url_for('register'))
        else :
            if not(pbkdf2_sha256.verify(re_password,password)):
                print((pbkdf2_sha256.verify(re_password,password)))
                return "Invalid Password"
            else:
            # name = form.name.data
                print([email,password,re_password])
                sql = ''' INSERT INTO users(email, password) 
                    VALUES(%s,%s);
                    '''
                cursor.execute(sql,(email,password))
                db.commit()
                # cursor.execute('SELECT * FROM users;')
                # users = cursor.fetchall()
                return render_template('login.html')
    else :
        return render_template('register.html')
    db.close()

@app.route("/login",methods = ['GET','POST'])
@is_logged_out
def login():
    if request.method == 'POST':
        id = request.form.get('email')
        pw = request.form.get('password')
        
        sql = 'SELECT * FROM users WHERE email = %s'
        cursor.execute(sql,[id])
        users = cursor.fetchone()


        if users ==None:
            return redirect(url_for('login'))
        else:
            if pbkdf2_sha256.verify(pw,users[2] ):
                session['is_logged'] = True
                session['email'] = users[1]
                return redirect(url_for('index'))
            else:
                return redirect(url_for('login'))
        
        return "Success"
    else:
        return render_template('login.html')
    db.close()

@app.route('/logout',methods = ['GET'])
@is_logged_in
def logout():
    session.clear()
    return redirect(url_for('login'))

@app.route("/data")
@is_logged_in
def data():
    sql = 'SELECT * FROM team3_data_1;'
    cursor.execute(sql)
    data = cursor.fetchall()
    # return "get success"
    return render_template("data.html", data = data)

@app.route("/tracking")
@is_logged_in
def trak():
    sql = 'SELECT * FROM team3_data_1;'
    cursor.execute(sql)
    x = 10
    y = 30
    plot.scatterchar(x,y)
    return redirect(request)
if __name__ =='__main__':
    # app.run(host='0.0.0.0', port='8080')
    app.secret_key = 'secretkey123456789'  # app.run(host = "0.0.0.0", port = "8080")
    app.run(port = '8000')