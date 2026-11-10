import tkinter as tk
from tkinter import messagebox
from database import get_db_connection

class DonationForm:
    def __init__(self, root, user):
        self.root = root
        self.user = user
        self.root.title("Add Food Donation")
        self.root.geometry("400x350")

        tk.Label(root, text="Food Donation Entry", font=("Arial", 12, "bold")).pack(pady=15)

        tk.Label(root, text="Food Item Description").pack(anchor="w", padx=40)
        self.item_entry = tk.Entry(root, width=30)
        self.item_entry.pack(pady=5, padx=40)

        tk.Label(root, text="Quantity (Meals/Units)").pack(anchor="w", padx=40)
        self.qty_entry = tk.Entry(root, width=30)
        self.qty_entry.pack(pady=5, padx=40)

        tk.Label(root, text="Expiry Datetime (YYYY-MM-DD HH:MM:SS)").pack(anchor="w", padx=40)
        self.expiry_entry = tk.Entry(root, width=30)
        self.expiry_entry.pack(pady=5, padx=40)

        tk.Button(root, text="Submit Donation", bg="#28a745", fg="white", command=self.save_donation).pack(pady=20)

    def save_donation(self):
        item = self.item_entry.get()
        qty = self.qty_entry.get()
        expiry = self.expiry_entry.get()

        if not item or not qty or not expiry:
            messagebox.showerror("Error", "All fields are required!")
            return

        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT * FROM Donors WHERE user_id = %s", (self.user['user_id'],))
        donor = cursor.fetchone()

        if donor:
            cursor.execute("INSERT INTO Food_Donations (donor_id, food_item, quantity, expiry_time, urgency_score) VALUES (%s, %s, %s, %s, 1)", 
                           (donor['donor_id'], item, qty, expiry))
            conn.commit()
            messagebox.showinfo("Success", "Donation listed successfully!")
            self.root.destroy()
        else:
            messagebox.showerror("Error", "Donor profile mapping not found.")
        cursor.close()
        conn.close()