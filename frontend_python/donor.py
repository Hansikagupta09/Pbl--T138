import customtkinter as ctk
from tkinter import messagebox
from database import get_db_connection, get_donor_id_by_user

class DonorDashboard:
    def __init__(self, root, user):
        self.root = root
        self.user = user
        self.root.title(f"Share-a-Plate | Donor Portal - {user['name']}")
        self.root.geometry("900x600")

        # Top Bar
        header = ctk.CTkFrame(root, height=60, fg_color="#1a2e26", corner_radius=0)
        header.pack(fill="x", side="top")
        ctk.CTkLabel(header, text=f"📦 Donor Dashboard: {user['name']}", font=ctk.CTkFont(size=16, weight="bold"), text_color="white").pack(side="left", padx=25)
        ctk.CTkButton(header, text="Logout", width=80, fg_color="#e63946", hover_color="#c5222f", command=root.destroy).pack(side="right", padx=25)

        # Main Body Split (Left: Form to add donation, Right: Active donations list)
        body = ctk.CTkFrame(root, fg_color="transparent")
        body.pack(fill="both", expand=True, padx=30, pady=20)

        # Left Column: Add Donation Form
        form_frame = ctk.CTkFrame(body, width=350, corner_radius=12)
        form_frame.pack(side="left", fill="y", padx=(0, 15))
        form_frame.pack_propagate(False)

        ctk.CTkLabel(form_frame, text="Add New Surplus Food", font=ctk.CTkFont(size=15, weight="bold")).pack(pady=(20, 10))

        ctk.CTkLabel(form_frame, text="Food Item & Description", font=ctk.CTkFont(size=11, weight="bold")).pack(anchor="w", padx=25)
        self.item_entry = ctk.CTkEntry(form_frame, placeholder_text="e.g., Cooked Rice & Dal (50 plates)", width=280, height=35)
        self.item_entry.pack(pady=(0, 12), padx=25)

        ctk.CTkLabel(form_frame, text="Quantity (Units/Meals)", font=ctk.CTkFont(size=11, weight="bold")).pack(anchor="w", padx=25)
        self.qty_entry = ctk.CTkEntry(form_frame, placeholder_text="50", width=280, height=35)
        self.qty_entry.pack(pady=(0, 12), padx=25)

        ctk.CTkLabel(form_frame, text="Expiry Time (YYYY-MM-DD HH:MM:SS)", font=ctk.CTkFont(size=11, weight="bold")).pack(anchor="w", padx=25)
        self.expiry_entry = ctk.CTkEntry(form_frame, placeholder_text="2026-10-07 18:00:00", width=280, height=35)
        self.expiry_entry.pack(pady=(0, 20), padx=25)

        ctk.CTkButton(form_frame, text="Broadcast Donation", width=280, height=40, fg_color="#28a745", hover_color="#218838", font=ctk.CTkFont(size=13, weight="bold"), command=self.submit_donation).pack(padx=25)

        # Right Column: Live Donations History Table/Scroll
        list_frame = ctk.CTkFrame(body, corner_radius=12)
        list_frame.pack(side="right", fill="both", expand=True)

        ctk.CTkLabel(list_frame, text="Your Donated Food Records", font=ctk.CTkFont(size=15, weight="bold")).pack(pady=(20, 10))
        
        self.scroll_list = ctk.CTkScrollableFrame(list_frame, fg_color="transparent", width=450, height=400)
        self.scroll_list.pack(fill="both", expand=True, padx=20, pady=10)
        self.load_donations()

    def submit_donation(self):
        item = self.item_entry.get().strip()
        qty = self.qty_entry.get().strip()
        expiry = self.expiry_entry.get().strip()

        if not item or not qty or not expiry:
            messagebox.showerror("Error", "All fields are required!")
            return

        donor_id = get_donor_id_by_user(self.user['user_id'])
        if not donor_id:
            messagebox.showerror("Error", "Donor profile mapping not found in database.")
            return

        try:
            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("INSERT INTO Food_Donations (donor_id, food_item, quantity, expiry_time, urgency_score) VALUES (%s, %s, %s, %s, 1)", 
                           (donor_id, item, int(qty), expiry))
            conn.commit()
            cursor.close()
            conn.close()
            messagebox.showinfo("Success", "Food donation listed successfully!")
            self.item_entry.delete(0, 'end')
            self.qty_entry.delete(0, 'end')
            self.expiry_entry.delete(0, 'end')
            self.load_donations()
        except Exception as e:
            messagebox.showerror("Database Error", str(e))

    def load_donations(self):
        for widget in self.scroll_list.winfo_children():
            widget.destroy()

        donor_id = get_donor_id_by_user(self.user['user_id'])
        if not donor_id: return

        conn = get_db_connection()
        if not conn: return
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT * FROM Food_Donations WHERE donor_id = %s ORDER BY donation_id DESC", (donor_id,))
        records = cursor.fetchall()
        cursor.close()
        conn.close()

        if not records:
            ctk.CTkLabel(self.scroll_list, text="No active donations listed yet.", text_color="gray").pack(pady=20)
            return

        for r in records:
            card = ctk.CTkFrame(self.scroll_list, fg_color="#f4f6f9", corner_radius=8)
            card.pack(fill="x", pady=5, padx=5)
            text_info = f"🍱 Item: {r['food_item']} | Qty: {r['quantity']} units\n⏳ Expiry: {r['expiry_time']}"
            ctk.CTkLabel(card, text=text_info, font=ctk.CTkFont(size=12), text_color="#333", justify="left").pack(anchor="w", padx=15, pady=10)