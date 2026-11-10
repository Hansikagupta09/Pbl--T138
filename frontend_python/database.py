import mysql.connector
from mysql.connector import Error

def get_db_connection():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='share_a_plate',
            user='root',
            password='ShareAplate@12' # Put your MySQL password here if configured
        )
        if connection.is_connected():
            return connection
    except Error as e:
        print(f"Database connection error: {e}")
        return None

def authenticate_user(email):
    conn = get_db_connection()
    if not conn: return None
    cursor = conn.cursor(dictionary=True)
    cursor.execute("SELECT * FROM Users WHERE email = %s", (email,))
    user = cursor.fetchone()
    cursor.close()
    conn.close()
    return user

def get_donor_id_by_user(user_id):
    conn = get_db_connection()
    if not conn: return None
    cursor = conn.cursor(dictionary=True)
    cursor.execute("SELECT donor_id FROM Donors WHERE user_id = %s", (user_id,))
    res = cursor.fetchone()
    cursor.close()
    conn.close()
    return res['donor_id'] if res else None

def get_ngo_id_by_user(user_id):
    conn = get_db_connection()
    if not conn: return None
    cursor = conn.cursor(dictionary=True)
    cursor.execute("SELECT ngo_id FROM NGOs WHERE user_id = %s", (user_id,))
    res = cursor.fetchone()
    cursor.close()
    conn.close()
    return res['ngo_id'] if res else None