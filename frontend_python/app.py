from flask import Flask, render_template_string, request, redirect, url_for, session
import mysql.connector
import re

app = Flask(__name__)
app.secret_key = "share_a_plate_master_secure_key"

def get_db():
    return mysql.connector.connect(
        host='localhost',
        database='share_a_plate',
        user='root',
        password='ShareAplate@12'
    )

def is_current_admin():
    user_id = session.get('user_id')
    if not user_id or session.get('role') != 'Admin':
        return False
    db = None
    cursor = None
    try:
        db = get_db()
        cursor = db.cursor()
        cursor.execute("SELECT user_id FROM Users WHERE user_id = %s AND role = 'Admin'", (user_id,))
        return cursor.fetchone() is not None
    except mysql.connector.Error:
        return False
    finally:
        if cursor:
            cursor.close()
        if db:
            db.close()

COMMON_STYLE = """
<style>
    body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: #f4f6f9; margin: 0; padding: 0; color: #333; }
    header { background-color: #1a2e26; color: white; padding: 15px 30px; display: flex; justify-content: space-between; align-items: center; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }
    header h2 { margin: 0; font-size: 20px; }
    .logout-btn { background-color: #e63946; color: white; border: none; padding: 8px 16px; border-radius: 5px; cursor: pointer; text-decoration: none; font-weight: bold; font-size: 13px; }
    .logout-btn:hover { background-color: #c5222f; }
    .container { max-width: 1000px; margin: 30px auto; background: white; padding: 35px; border-radius: 12px; box-shadow: 0 4px 15px rgba(0,0,0,0.05); }
    h3 { color: #1a2e26; margin-top: 0; }
    .card { background: #f8f9fa; border-left: 4px solid #28a745; padding: 18px; margin-bottom: 15px; border-radius: 6px; box-shadow: 0 2px 5px rgba(0,0,0,0.02); }
    .btn-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 15px; margin: 20px 0 30px 0; }
    .db-btn { background-color: #343a40; color: white; padding: 14px 20px; border: none; border-radius: 8px; font-weight: bold; cursor: pointer; text-align: center; text-decoration: none; display: block; font-size: 14px; transition: 0.2s; }
    .db-btn:hover { background-color: #212529; transform: translateY(-2px); }
    .db-btn.active { background-color: #28a745; }
    form input, form select, form button { width: 100%; padding: 11px; margin: 8px 0 16px 0; border: 1px solid #ced4da; border-radius: 6px; box-sizing: border-box; font-size: 14px; }
    form button { background-color: #28a745; color: white; border: none; font-weight: bold; cursor: pointer; }
    form button:hover { background-color: #218838; }
    .auth-box { width: min(400px, calc(100% - 40px)); margin: 60px auto; background: white; padding: 30px; border-radius: 12px; box-shadow: 0 6px 20px rgba(0,0,0,0.08); box-sizing: border-box; }
    .auth-box h2 { text-align: center; color: #1a2e26; margin-top: 0; }
    .link-text { text-align: center; margin-top: 15px; font-size: 13px; }
    .link-text a { color: #28a745; text-decoration: none; font-weight: bold; }
    .table-card { background: white; border: 1px solid #e9ecef; border-left: 4px solid #007bff; padding: 15px; margin-bottom: 12px; border-radius: 6px; overflow-wrap: anywhere; }
    .table-wrap { width: 100%; overflow-x: auto; border: 1px solid #e5e7eb; border-radius: 8px; margin: 18px 0 28px; }
    table { border-collapse: collapse; width: 100%; min-width: 900px; background: white; font-size: 13px; }
    th, td { padding: 10px; border-bottom: 1px solid #e5e7eb; border-right: 1px solid #edf0f2; text-align: left; vertical-align: top; }
    th { background: #1a2e26; color: white; position: sticky; top: 0; }
    tr:nth-child(even) { background: #f8faf9; }
    td input, td select { min-width: 120px; width: 100%; padding: 7px; border: 1px solid #ced4da; border-radius: 4px; box-sizing: border-box; }
    .small-btn { width: auto; padding: 7px 10px; margin: 3px; border-radius: 5px; border: 0; cursor: pointer; font-weight: bold; }
    .save-btn { background: #198754; color: white; }
    .delete-btn { background: #dc3545; color: white; }
    .add-panel { border: 1px solid #dbe5dd; background: #f8fbf8; padding: 18px; border-radius: 8px; margin: 20px 0; }
    .add-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(210px, 1fr)); gap: 10px 16px; }
    .add-grid label { display: block; font-size: 13px; font-weight: 600; }
    .add-grid input, .add-grid select { width: 100%; padding: 9px; margin: 6px 0 12px; border: 1px solid #ced4da; border-radius: 5px; box-sizing: border-box; }
    .muted { color: #667085; font-size: 12px; }
    .notice { padding: 12px; border-radius: 6px; background: #fff3cd; color: #664d03; margin: 12px 0; }
    .back-link { display: inline-block; margin: 8px 0 20px; color: #218838; font-weight: bold; text-decoration: none; }
    @media (max-width: 600px) { .container { margin: 12px; padding: 18px; } header { padding: 14px; gap: 12px; } header h2 { font-size: 16px; } }
</style>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        email = request.form['email'].strip()
        db = get_db()
        cursor = db.cursor(dictionary=True)
        cursor.execute("SELECT * FROM Users WHERE email = %s", (email,))
        user = cursor.fetchone()
        cursor.close()
        db.close()

        if user:
            session['user_id'] = user['user_id']
            session['name'] = user['name']
            session['email'] = user['email']
            session['role'] = user['role']
            
            if user['role'] == 'Admin':
                return redirect(url_for('admin_dashboard'))
            elif user['role'] == 'Donor':
                return redirect(url_for('donor_dashboard'))
            elif user['role'] == 'NGO':
                return redirect(url_for('ngo_dashboard'))
        else:
            error = "Account not found."

    html = COMMON_STYLE + """
    <div class="auth-box">
        <h2>🌿 Share-a-Plate</h2>
        {% if error %}<p style="color:red; font-size:12px; text-align:center;">{{ error }}</p>{% endif %}
        <form method="POST">
            <label><strong>Email Address</strong></label>
            <input type="email" name="email" required>
            <button type="submit">Login</button>
        </form>
        <div class="link-text">
            <a href="/register">Register</a>
        </div>
        <div class="link-text">
            <a href="/admin-login">Admin Login</a>
        </div>
        <div class="link-text">
            <a href="/admin-register">First Admin Setup</a>
        </div>
    </div>
    """
    return render_template_string(html, error=error)

@app.route('/register', methods=['GET', 'POST'])
def register():
    error = None

    if request.method == 'POST':
        name = request.form['name'].strip()
        email = request.form['email'].strip()
        phone = request.form['phone'].strip()
        role = request.form['role']
        org_name = request.form.get('org_name', '').strip()
        address = request.form.get('address', '').strip()

        if role not in ('Donor', 'NGO'):
            error = "Invalid role selected."
        else:
            db = get_db()
            cursor = db.cursor(dictionary=True)
            try:
                cursor.execute("SELECT * FROM Users WHERE email = %s", (email,))
                if cursor.fetchone():
                    error = "Email already registered."
                else:
                    cursor.execute("INSERT INTO Users (name, email, phone, role) VALUES (%s, %s, %s, %s)", 
                                   (name, email, phone, role))
                    user_id = cursor.lastrowid

                    if role == 'Donor':
                        cursor.execute("INSERT INTO Donors (user_id, organization_name, address) VALUES (%s, %s, %s)", 
                                       (user_id, org_name, address))
                    elif role == 'NGO':
                        cursor.execute("INSERT INTO NGOs (user_id, organization_name, capacity, address) VALUES (%s, %s, %s, %s)", 
                                       (user_id, org_name, 100, address))

                    db.commit()
                    cursor.close()
                    db.close()
                    return redirect(url_for('login'))
            except Exception as e:
                error = f"Database Error: {e}"
            finally:
                if 'cursor' in locals() and cursor: cursor.close()
                if 'db' in locals() and db: db.close()

    html = COMMON_STYLE + """
    <div class="auth-box" style="width: 450px;">
        <h2>📝 Register</h2>
        {% if error %}<p style="color:red; font-size:12px; text-align:center;">{{ error }}</p>{% endif %}
        <form method="POST">
            <label><strong>Full Name</strong></label>
            <input type="text" name="name" required>
            
            <label><strong>Email Address</strong></label>
            <input type="email" name="email" required>
            
            <label><strong>Phone Number</strong></label>
            <input type="text" name="phone" required>
            
            <label><strong>Select Role</strong></label>
            <select name="role" id="roleSelect" onchange="toggleOrgFields()">
                <option value="Donor">Donor</option>
                <option value="NGO">NGO</option>
            </select>

            <div id="orgFields">
                <label><strong>Organization Name</strong></label>
                <input type="text" name="org_name">
                
                <label><strong>Address</strong></label>
                <input type="text" name="address">
            </div>

            <button type="submit">Register</button>
        </form>
        <div class="link-text">
            <a href="/">Login</a>
        </div>
    </div>
    <script>
        function toggleOrgFields() {
            var role = document.getElementById('roleSelect').value;
            var orgFields = document.getElementById('orgFields');
            if(role === 'Admin') {
                orgFields.style.display = 'none';
            } else {
                orgFields.style.display = 'block';
            }
        }
    </script>
    """
    return render_template_string(html, error=error)

@app.route('/admin-login', methods=['GET', 'POST'])
def admin_login():
    error = None
    if request.method == 'POST':
        email = request.form['email'].strip()
        db = get_db()
        cursor = db.cursor(dictionary=True)
        cursor.execute("SELECT * FROM Users WHERE email = %s AND role = 'Admin'", (email,))
        admin = cursor.fetchone()
        cursor.close()
        db.close()

        if admin:
            session['user_id'] = admin['user_id']
            session['name'] = admin['name']
            session['email'] = admin['email']
            session['role'] = admin['role']
            return redirect(url_for('admin_dashboard'))
        error = "Admin account not found."

    html = COMMON_STYLE + """
    <div class="auth-box">
        <h2>⚙️ Admin Login</h2>
        {% if error %}<p style="color:red; font-size:12px; text-align:center;">{{ error }}</p>{% endif %}
        <form method="POST">
            <label><strong>Email</strong></label>
            <input type="email" name="email" required>
            <button type="submit">Login</button>
        </form>
        <div class="link-text"><a href="/">Back</a></div>
    </div>
    """
    return render_template_string(html, error=error)

@app.route('/admin')
def admin_dashboard():
    if not is_current_admin():
        session.clear()
        return redirect(url_for('admin_login'))

    tables = [
        ('users', '👥 All Users'),
        ('donors', '🍽️ Donors'),
        ('ngos', '🤝 NGOs'),
        ('donations', '📦 Donations'),
        ('food_donations', '🥗 Food Donations'),
        ('food_requests', '📋 Food Requests'),
        ('allocations', '🧾 Allocations'),
        ('tracking', '🚚 Tracking'),
        ('quality_verification', '✅ Quality Verification'),
        ('feedback', '💬 Feedback'),
    ]
    html = COMMON_STYLE + """
    <header><h2>⚙️ Admin Dashboard</h2><a href="/logout" class="logout-btn">Logout</a></header>
    <div class="container">
        <h3>Welcome, {{ session['name'] }}</h3>
        <div class="btn-grid">
        {% for table_name, label in tables %}
            <a href="{{ url_for('admin_table', table_name=table_name) }}" class="db-btn">{{ label }}</a>
        {% endfor %}
        </div>
        <h3>Admin Tools</h3>
        <div class="btn-grid">
            <a href="{{ url_for('manage_admins') }}" class="db-btn">🛡️ Manage Admin Accounts</a>
            <a href="{{ url_for('admin_table', table_name='users') }}" class="db-btn">✏️ Manage Users</a>
        </div>
    </div>
    """
    return render_template_string(html, tables=tables)

ADMIN_TABLES = {
    'users', 'donors', 'ngos', 'donations', 'food_donations',
    'food_requests', 'allocations', 'tracking', 'quality_verification', 'feedback'
}

def get_table_metadata(cursor, table_name):
    cursor.execute("""
        SELECT COLUMN_NAME, DATA_TYPE, COLUMN_TYPE, IS_NULLABLE,
               COLUMN_DEFAULT, EXTRA, COLUMN_KEY
        FROM information_schema.COLUMNS
        WHERE TABLE_SCHEMA = %s AND TABLE_NAME = %s
        ORDER BY ORDINAL_POSITION
    """, ('share_a_plate', table_name))
    columns = cursor.fetchall()
    for col in columns:
        col['enum_values'] = []
        if col['DATA_TYPE'].lower() == 'enum':
            col['enum_values'] = re.findall(r"'((?:[^'\\]|\\.)*)'", col['COLUMN_TYPE'])
        col['is_auto'] = 'auto_increment' in (col['EXTRA'] or '').lower()
        col['is_generated'] = 'generated' in (col['EXTRA'] or '').lower()
        col['is_required'] = col['IS_NULLABLE'] == 'NO' and col['COLUMN_DEFAULT'] is None and not col['is_auto'] and not col['is_generated']
        col['is_primary'] = col['COLUMN_KEY'] == 'PRI'
        col['input_type'] = 'text'
        if col['DATA_TYPE'].lower() in ('int', 'bigint', 'smallint', 'mediumint', 'tinyint', 'decimal', 'float', 'double'):
            col['input_type'] = 'number'
        elif col['DATA_TYPE'].lower() == 'date':
            col['input_type'] = 'date'
        elif col['DATA_TYPE'].lower() in ('datetime', 'timestamp'):
            col['input_type'] = 'datetime-local'
        elif col['DATA_TYPE'].lower() == 'time':
            col['input_type'] = 'time'
        elif col['DATA_TYPE'].lower() in ('text', 'mediumtext', 'longtext'):
            col['input_type'] = 'text'
    return columns

@app.route('/admin/table/<table_name>', methods=['GET', 'POST'])
def admin_table(table_name):
    if not is_current_admin():
        session.clear()
        return redirect(url_for('admin_login'))
    if table_name not in ADMIN_TABLES:
        return "Table not found", 404

    db = None
    cursor = None
    rows, columns, error, success = [], [], None, None
    title = table_name.replace('_', ' ').title()
    try:
        db = get_db()
        cursor = db.cursor(dictionary=True)
        columns = get_table_metadata(cursor, table_name)
        if not columns:
            raise ValueError('Table does not exist.')
        primary_keys = [c['COLUMN_NAME'] for c in columns if c['is_primary']]
        if len(primary_keys) != 1:
            raise ValueError('Primary key requirement not met.')
        pk = primary_keys[0]
        col_names = [c['COLUMN_NAME'] for c in columns]
        column_map = {c['COLUMN_NAME']: c for c in columns}

        if request.method == 'POST':
            action = request.form.get('action', '')
            try:
                if action == 'add':
                    insert_cols, values = [], []
                    for col in columns:
                        name = col['COLUMN_NAME']
                        if col['is_auto'] or col['is_generated']:
                            continue
                        raw = request.form.get('field_' + name, '').strip()
                        if raw == '' and (col['COLUMN_DEFAULT'] is not None or col['IS_NULLABLE'] == 'YES'):
                            continue
                        if raw == '' and col['is_required']:
                            raise ValueError(f"{name} is required.")
                        if raw != '':
                            insert_cols.append(name)
                            if col['DATA_TYPE'].lower() in ('datetime', 'timestamp') and 'T' in raw:
                                raw = raw.replace('T', ' ')
                            values.append(raw)
                    if not insert_cols:
                        raise ValueError('No values provided.')
                    cols_sql = ', '.join('`' + c + '`' for c in insert_cols)
                    placeholders = ', '.join(['%s'] * len(values))
                    cursor.execute(f"INSERT INTO `{table_name}` ({cols_sql}) VALUES ({placeholders})", tuple(values))
                    db.commit()
                    success = 'Record added.'

                elif action == 'update':
                    record_id = request.form.get('record_id', '')
                    updates, values = [], []
                    for col in columns:
                        name = col['COLUMN_NAME']
                        if name == pk or col['is_auto'] or col['is_generated']:
                            continue
                        field_key = 'field_' + name
                        if field_key not in request.form:
                            continue
                        raw = request.form.get(field_key, '').strip()
                        if raw == '' and col['IS_NULLABLE'] == 'YES':
                            raw_value = None
                        elif raw == '' and col['COLUMN_DEFAULT'] is not None:
                            continue
                        elif raw == '' and col['is_required']:
                            raise ValueError(f"{name} required.")
                        else:
                            raw_value = raw if raw != '' else None
                        if isinstance(raw_value, str) and col['DATA_TYPE'].lower() in ('datetime', 'timestamp') and 'T' in raw_value:
                            raw_value = raw_value.replace('T', ' ')
                        updates.append('`' + name + '` = %s')
                        values.append(raw_value)
                    if not updates:
                        raise ValueError('No updates provided.')
                    values.append(record_id)
                    cursor.execute(f"UPDATE `{table_name}` SET {', '.join(updates)} WHERE `{pk}` = %s", tuple(values))
                    db.commit()
                    success = 'Record updated.' if cursor.rowcount else 'No changes made.'

                elif action == 'delete':
                    record_id = request.form.get('record_id', '')
                    if table_name == 'users' and str(record_id) == str(session.get('user_id')):
                        raise ValueError('Cannot delete active admin.')
                    cursor.execute(f"DELETE FROM `{table_name}` WHERE `{pk}` = %s", (record_id,))
                    db.commit()
                    success = 'Record removed.' if cursor.rowcount else 'Record not found.'
            except Exception as e:
                db.rollback()
                error = f'Error: {e}'

        cursor.execute(f"SELECT * FROM `{table_name}` ORDER BY `{pk}` DESC")
        rows = cursor.fetchall()
    except Exception as e:
        error = str(e)
    finally:
        if cursor:
            cursor.close()
        if db:
            db.close()

    editable_columns = [c for c in columns if not c['is_auto'] and not c['is_generated'] and not c['is_primary']]
    add_columns = [c for c in columns if not c['is_auto'] and not c['is_generated']]
    html = COMMON_STYLE + """
    <header><h2>ShareAPlate — {{ title }}</h2><a href="/logout" class="logout-btn">Logout</a></header>
    <div class="container">
        <a class="back-link" href="{{ url_for('admin_dashboard') }}">← Back</a>
        <h3>{{ title }}</h3>
        {% if error %}<div class="notice">{{ error }}</div>{% endif %}
        {% if success %}<div class="card">{{ success }}</div>{% endif %}

        <div class="add-panel">
            <h3>＋ Add New Record</h3>
            <form method="POST">
                <input type="hidden" name="action" value="add">
                <div class="add-grid">
                {% for col in add_columns %}
                    <label>{{ col['COLUMN_NAME'].replace('_', ' ').title() }}{% if col['is_required'] %} *{% endif %}
                    {% if col['enum_values'] %}
                        <select name="field_{{ col['COLUMN_NAME'] }}" {% if col['is_required'] %}required{% endif %}>
                            <option value="">Select...</option>
                            {% for option in col['enum_values'] %}<option value="{{ option }}">{{ option }}</option>{% endfor %}
                        </select>
                    {% else %}
                        <input type="{{ col['input_type'] }}" name="field_{{ col['COLUMN_NAME'] }}" {% if col['is_required'] %}required{% endif %} {% if col['input_type'] == 'number' %}step="any"{% endif %}>
                    {% endif %}
                    </label>
                {% endfor %}
                </div>
                <button type="submit">Add</button>
            </form>
        </div>

        <h3>Records</h3>
        {% if rows %}
        <div class="table-wrap"><table>
            <thead><tr>
                {% for col in columns %}<th>{{ col['COLUMN_NAME'].replace('_', ' ').title() }}</th>{% endfor %}
                <th>Actions</th>
            </tr></thead>
            <tbody>
            {% for row in rows %}
                {% set row_index = loop.index %}
                <tr>
                    {% for col in columns %}
                        {% set cname = col['COLUMN_NAME'] %}
                        <td>
                        {% if cname == pk or col['is_auto'] or col['is_generated'] %}
                            {{ row[cname] if row[cname] is not none else '—' }}
                        {% elif col['is_primary'] %}
                            {{ row[cname] if row[cname] is not none else '—' }}
                        {% elif col['enum_values'] %}
                            <select form="row-{{ row_index }}" name="field_{{ cname }}">
                                {% for option in col['enum_values'] %}<option value="{{ option }}" {% if row[cname]|string == option %}selected{% endif %}>{{ option }}</option>{% endfor %}
                            </select>
                        {% else %}
                            <input form="row-{{ row_index }}" type="{{ col['input_type'] }}" name="field_{{ cname }}" value="{{ row[cname]|string if row[cname] is not none else '' }}" {% if col['is_required'] %}required{% endif %} {% if col['input_type'] == 'number' %}step="any"{% endif %}>
                        {% endif %}
                        </td>
                    {% endfor %}
                    <td style="min-width:150px;">
                        <form method="POST" id="row-{{ row_index }}">
                            <input type="hidden" name="record_id" value="{{ row[pk] }}">
                            <button class="small-btn save-btn" type="submit" name="action" value="update">Update</button>
                            <button class="small-btn delete-btn" type="submit" name="action" value="delete" onclick="return confirm('Delete record?');">Remove</button>
                        </form>
                    </td>
                </tr>
            {% endfor %}
            </tbody>
        </table></div>
        {% else %}<p>No records found.</p>{% endif %}
    </div>
    """
    return render_template_string(html, title=title, rows=rows, columns=columns,
                                  add_columns=add_columns, editable_columns=editable_columns,
                                  pk=next((c['COLUMN_NAME'] for c in columns if c['is_primary']), 'id'),
                                  error=error, success=success)

@app.route('/admin/manage-admins', methods=['GET', 'POST'])
def manage_admins():
    if not is_current_admin():
        session.clear()
        return redirect(url_for('admin_login'))

    error = None
    success = None
    db = None
    cursor = None
    try:
        db = get_db()
        cursor = db.cursor(dictionary=True)

        if request.method == 'POST':
            name = request.form.get('name', '').strip()
            email = request.form.get('email', '').strip().lower()
            phone = request.form.get('phone', '').strip()

            if not name or not email or not phone:
                error = 'All fields required.'
            else:
                cursor.execute("SELECT user_id FROM Users WHERE email = %s", (email,))
                if cursor.fetchone():
                    error = 'Email already registered.'
                else:
                    cursor.execute(
                        "INSERT INTO Users (name, email, phone, role) VALUES (%s, %s, %s, 'Admin')",
                        (name, email, phone)
                    )
                    db.commit()
                    success = 'Admin created.'

        cursor.execute(
            "SELECT user_id, name, email, phone, created_at FROM Users WHERE role = 'Admin' ORDER BY user_id"
        )
        admins = cursor.fetchall()
    except Exception as e:
        if db:
            db.rollback()
        error = f'Database error: {e}'
        admins = []
    finally:
        if cursor:
            cursor.close()
        if db:
            db.close()

    html = COMMON_STYLE + """
    <header>
        <h2>🛡️ Manage Admins</h2>
        <a href="/logout" class="logout-btn">Logout</a>
    </header>
    <div class="container">
        <a class="back-link" href="{{ url_for('admin_dashboard') }}">← Back</a>
        <h3>Create Admin</h3>
        {% if error %}<div class="notice">{{ error }}</div>{% endif %}
        {% if success %}<div class="card">{{ success }}</div>{% endif %}
        <form method="POST">
            <label><strong>Name</strong></label>
            <input type="text" name="name" required>
            <label><strong>Email</strong></label>
            <input type="email" name="email" required>
            <label><strong>Phone</strong></label>
            <input type="text" name="phone" required>
            <button type="submit">Create</button>
        </form>

        <h3>Existing Admins</h3>
        {% for admin in admins %}
            <div class="table-card">
                <strong>ID:</strong> {{ admin.user_id }}<br>
                <strong>Name:</strong> {{ admin.name }}<br>
                <strong>Email:</strong> {{ admin.email }}<br>
                <strong>Phone:</strong> {{ admin.phone }}<br>
                <strong>Created:</strong> {{ admin.created_at }}
            </div>
        {% else %}
            <p>No admins found.</p>
        {% endfor %}
    </div>
    """
    return render_template_string(html, admins=admins, error=error, success=success)

@app.route('/admin-register', methods=['GET', 'POST'])
def admin_register():
    error = None
    db = None
    cursor = None
    try:
        db = get_db()
        cursor = db.cursor(dictionary=True)
        cursor.execute("SELECT user_id FROM Users WHERE role = 'Admin' LIMIT 1")
        existing_admin = cursor.fetchone()

        if existing_admin:
            html = COMMON_STYLE + """
            <div class="auth-box">
                <h2>Restricted</h2>
                <p>Admin already exists.</p>
                <div class="link-text"><a href="/admin-login">Login</a></div>
            </div>
            """
            return render_template_string(html), 403

        if request.method == 'POST':
            name = request.form.get('name', '').strip()
            email = request.form.get('email', '').strip().lower()
            phone = request.form.get('phone', '').strip()
            if not name or not email or not phone:
                error = 'All fields required.'
            else:
                cursor.execute("SELECT user_id FROM Users WHERE email = %s", (email,))
                if cursor.fetchone():
                    error = 'Email already registered.'
                else:
                    cursor.execute(
                        "INSERT INTO Users (name, email, phone, role) VALUES (%s, %s, %s, 'Admin')",
                        (name, email, phone)
                    )
                    db.commit()
                    return redirect(url_for('admin_login'))
    except Exception as e:
        if db:
            db.rollback()
        error = f'Database error: {e}'
    finally:
        if cursor:
            cursor.close()
        if db:
            db.close()

    html = COMMON_STYLE + """
    <div class="auth-box">
        <h2>🛡️ Register First Admin</h2>
        {% if error %}<p style="color:red; font-size:12px; text-align:center;">{{ error }}</p>{% endif %}
        <form method="POST">
            <label><strong>Name</strong></label>
            <input type="text" name="name" required>
            <label><strong>Email</strong></label>
            <input type="email" name="email" required>
            <label><strong>Phone</strong></label>
            <input type="text" name="phone" required>
            <button type="submit">Create</button>
        </form>
        <div class="link-text"><a href="/">Login</a></div>
    </div>
    """
    return render_template_string(html, error=error)

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)