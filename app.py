from flask import Flask, render_template,flash,redirect,url_for,session,request,logging      # render_template : 요청한 클라이언트에 HTML형식으로 문서화 시켜서 보내는 Class
from passlib.hash import pbkdf2_sha256
import pymysql
from functools import wraps

app = Flask(__name__)
app.debug=True

db = pymysql.connect(host = 'localhost', port = 3306, user = 'root', passwd='1234',db = 'myflaskapp')
cursor = db.cursor()

@app.route('/')
def index():
    print("Success")
    # return "TEST"
    return render_template('home.html')



@app.route("/register",methods=['GET','Post'])
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
                return redirect(url_for('login'))
    else :
        return render_template('register.html')
    db.close()

@app.route("/login",methods = ['GET','POST'])
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
                session['email'] = users[1]
                return redirect('/')
            else:
                return redirect(url_for('login'))
        
        return "Success"
    else:
        return render_template('login.html')
    db.close()

@app.route("/data")
def data():
    sql = 'SELECT * FROM team3_data_1;'
    cursor.execute(sql)
    data = cursor.fetchall()
    # return "get success"
    return render_template("data.html", data = data)


if __name__ =='__main__':
    # app.run(host='0.0.0.0', port='8080')
    app.secret_key = 'secretkey123456789'  # app.run(host = "0.0.0.0", port = "8080")
    app.run(port = '8000')