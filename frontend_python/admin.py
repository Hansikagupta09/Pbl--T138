import customtkinter as ctk
import subprocess
from tkinter import messagebox
from database import get_db_connection

class AdminDashboard:
    def __init__(self, root, user):
        self.root = root
        self.user = user
        self.root.title("Share-a-Plate | Admin Control Center")
        self.root.geometry("950x650")

        # Top Bar
        header = ctk.CTkFrame(root, height=60, fg_color="#1a2e26", corner_radius=0)
        header.pack(fill="x", side="top")
        ctk.CTkLabel(header, text="⚙️ Admin Command Center - System Oversight", font=ctk.CTkFont(size=16, weight="bold"), text_color="white").pack(side="left", padx=25)
        ctk.CTkButton(header, text="Logout", width=80, fg_color="#e63946", hover_color="#c5222f", command=root.destroy).pack(side="right", padx=25)

        body = ctk.CTkFrame(root, fg_color="transparent")
        body.pack(fill="both", expand=True, padx=30, pady=20)

        # Left Column: C Backend Engine Executor
        c_frame = ctk.CTkFrame(body, width=380, corner_radius=12)
        c_frame.pack(side="left", fill="y", padx=(0, 15))
        c_frame.pack_propagate(False)

        ctk.CTkLabel(c_frame, text="C Backend Engine Control", font=ctk.CTkFont(size=15, weight="bold")).pack(pady=(20, 10))
        ctk.CTkLabel(c_frame, text="Trigger compiled C algorithms directly", text_color="gray", font=ctk.CTkFont(size=11)).pack(pady=(0, 15))

        ctk.CTkButton(c_frame, text="⚡ Run Min-Heap Priority Queue Test", width=320, height=40, fg_color="#343a40", hover_color="#23272b", command=self.run_c_heap).pack(pady=10)
        ctk.CTkButton(c_frame, text="🗺️ Run Dijkstra Routing Algorithm", width=320, height=40, fg_color="#343a40", hover_color="#23272b", command=self.run_c_dijkstra).pack(pady=10)

        # Right Column: Master System Database Inspection
        master_frame = ctk.CTkFrame(body, corner_radius=12)
        master_frame.pack(side="right", fill="both", expand=True)

        ctk.CTkLabel(master_frame, text="Master User Directory", font=ctk.CTkFont(size=15, weight="bold")).pack(pady=(20, 5))

        self.user_scroll = ctk.CTkScrollableFrame(master_frame, fg_color="transparent", width=480, height=420)
        self.user_scroll.pack(fill="both", expand=True, padx=20, pady=10)
        self.load_all_users()

    def run_c_heap(self):
        try:
            result = subprocess.run(["../backend_c/backend_engine.exe", "test_heap"], capture_output=True, text=True, check=True)
            messagebox.showinfo("C Heap Engine Output", result.stdout)
        except Exception as e:
            messagebox.showerror("Execution Error", f"Ensure backend_engine.exe is compiled in backend_c/\n\n{e}")

    def run_c_dijkstra(self):
        try:
            result = subprocess.run(["../backend_c/backend_engine.exe", "test_dijkstra"], capture_output=True, text=True, check=True)
            messagebox.showinfo("C Dijkstra Routing Output", result.stdout)
        except Exception as e:
            messagebox.showerror("Execution Error", f"Ensure backend_engine.exe is compiled in backend_c/\n\n{e}")

    def load_all_users(self):
        for widget in self.user_scroll.winfo_children():
            widget.destroy()

        conn = get_db_connection()
        if not conn: return
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT * FROM Users ORDER BY user_id DESC")
        users = cursor.fetchall()
        cursor.close()
        conn.close()

        if not users:
            ctk.CTkLabel(self.user_scroll, text="No users registered in system.", text_color="gray").pack(pady=20)
            return

        for u in users:
            card = ctk.CTkFrame(self.user_scroll, fg_color="#f4f6f9", corner_radius=8)
            card.pack(fill="x", pady=5, padx=5)
            info = f"👤 ID: {u['user_id']} | Name: {u['name']}\n📧 Email: {u['email']} | Role: {u['role']}"
            ctk.CTkLabel(card, text=info, font=ctk.CTkFont(size=11), text_color="#333", justify="left").pack(anchor="w", padx=15, pady=10)