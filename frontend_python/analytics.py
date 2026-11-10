import tkinter as tk
from database import get_db_connection

class AnalyticsWindow:
    def __init__(self, root):
        self.root = root
        self.root.title("System Analytics & Waste Detection")
        self.root.geometry("450x350")

        tk.Label(root, text="Platform Overview Metrics", font=("Arial", 12, "bold")).pack(pady=15)

        self.stats_label = tk.Label(root, text="", font=("Arial", 11), justify="left")
        self.stats_label.pack(pady=10, padx=20, anchor="w")
        self.load_analytics()

    def load_analytics(self):
        conn = get_db_connection()
        cursor = conn.cursor()
        
        cursor.execute("SELECT COUNT(*) FROM Users")
        total_users = cursor.fetchone()[0]

        cursor.execute("SELECT SUM(quantity) FROM Food_Donations")
        total_food = cursor.fetchone()[0] or 0

        cursor.execute("SELECT COUNT(*) FROM Food_Requests")
        total_requests = cursor.fetchone()[0]

        cursor.close()
        conn.close()

        info = f"👥 Total Users Registered: {total_users}\n\n" \
               f"🍱 Total Food Donated (Units): {total_food}\n\n" \
               f"📋 Total NGO Requests Made: {total_requests}\n\n" \
               f"⚡ Status: System algorithms optimal & active."
        
        self.stats_label.config(text=info)