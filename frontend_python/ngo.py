import customtkinter as ctk
from tkinter import messagebox
from database import get_db_connection, get_ngo_id_by_user

class NGODashboard:
    def __init__(self, root, user):
        self.root = root
        self.user = user
        self.root.title(f"Share-a-Plate | NGO Portal - {user['name']}")
        self.root.geometry("900x600")

        # Top Bar
        header = ctk.CTkFrame(root, height=60, fg_color="#1a2e26", corner_radius=0)
        header.pack(fill="x", side="top")
        ctk.CTkLabel(header, text=f"🤝 NGO Dashboard: {user['name']}", font=ctk.CTkFont(size=16, weight="bold"), text_color="white").pack(side="left", padx=25)
        ctk.CTkButton(header, text="Logout", width=80, fg_color="#e63946", hover_color="#c5222f", command=root.destroy).pack(side="right", padx=25)

        # Main Layout
        body = ctk.CTkFrame(root, fg_color="transparent")
        body.pack(fill="both", expand=True, padx=30, pady=20)

        ctk.CTkLabel(body, text="Available Surplus Food Feed (Platform-Wide)", font=ctk.CTkFont(size=16, weight="bold")).pack(anchor="w", pady=(0, 10))

        # Scrollable Feed of Available Food Donations
        self.feed_frame = ctk.CTkScrollableFrame(body, fg_color="transparent", width=840, height=420)
        self.feed_frame.pack(fill="both", expand=True)
        self.load_surplus_feed()

    def load_surplus_feed(self):
        for widget in self.feed_frame.winfo_children():
            widget.destroy()

        conn = get_db_connection()
        if not conn: return
        cursor = conn.cursor(dictionary=True)
        cursor.execute("""
            SELECT fd.*, d.organization_name, d.address 
            FROM Food_Donations fd 
            JOIN Donors d ON fd.donor_id = d.donor_id 
            ORDER BY fd.created_at DESC
        """)
        donations = cursor.fetchall()
        cursor.close()
        conn.close()

        if not donations:
            ctk.CTkLabel(self.feed_frame, text="No surplus food available right now.", text_color="gray").pack(pady=30)
            return

        for d in donations:
            card = ctk.CTkFrame(self.feed_frame, fg_color="#f4f6f9", corner_radius=10)
            card.pack(fill="x", pady=8, padx=5)

            info_text = f"🏢 Donor: {d['organization_name']} ({d['address']})\n" \
                        f"🍱 Food Item: {d['food_item']} | Quantity: {d['quantity']} units\n" \
                        f"⏰ Expiry: {d['expiry_time']}"
            
            ctk.CTkLabel(card, text=info_text, font=ctk.CTkFont(size=12), text_color="#333", justify="left").pack(side="left", padx=15, pady=12)

            claim_btn = ctk.CTkButton(card, text="Request Allocation", fg_color="#28a745", hover_color="#218838", width=130, command=lambda did=d['donation_id']: self.request_allocation(did))
            claim_btn.pack(side="right", padx=20)

    def request_allocation(self, donation_id):
        ngo_id = get_ngo_id_by_user(self.user['user_id'])
        if not ngo_id:
            messagebox.showerror("Error", "NGO organizational mapping missing.")
            return

        try:
            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("INSERT INTO Food_Requests (ngo_id, required_quantity, status) VALUES (%s, 50, 'Pending')", (ngo_id,))
            conn.commit()
            cursor.close()
            conn.close()
            messagebox.showinfo("Success", "Food allocation requested successfully! Our routing engine will match and notify you.")
        except Exception as e:
            messagebox.showerror("Database Error", str(e))