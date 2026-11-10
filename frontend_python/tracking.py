import tkinter as tk
from database import get_db_connection

class TrackingWindow:
    def __init__(self, root):
        self.root = root
        self.root.title("Live Delivery Tracking")
        self.root.geometry("500x350")

        tk.Label(root, text="Active Allocation Tracking Chain", font=("Arial", 12, "bold")).pack(pady=15)

        self.text_area = tk.Text(root, width=55, height=15)
        self.text_area.pack(padx=20, pady=10)
        self.load_tracking_data()

    def load_tracking_data(self):
        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT t.tracking_id, a.allocation_id, t.current_status, t.updated_at FROM Tracking t JOIN Allocations a ON t.allocation_id = a.allocation_id")
        rows = cursor.fetchall()
        
        if not rows:
            self.text_area.insert(tk.END, "No active tracking chains found in database.\n")
        else:
            for row in rows:
                self.text_area.insert(tk.END, f"Tracking ID: {row['tracking_id']} | Allocation: {row['allocation_id']} | Status: {row['current_status']} | Time: {row['updated_at']}\n")
        cursor.close()
        conn.close()