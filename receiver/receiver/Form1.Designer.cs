namespace receiver
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.cmbportnames = new System.Windows.Forms.ComboBox();
            this.butopencom = new System.Windows.Forms.Button();
            this.butclosecom = new System.Windows.Forms.Button();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.cmdtb1 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // cmbportnames
            // 
            this.cmbportnames.FormattingEnabled = true;
            this.cmbportnames.Location = new System.Drawing.Point(13, 13);
            this.cmbportnames.Name = "cmbportnames";
            this.cmbportnames.Size = new System.Drawing.Size(121, 24);
            this.cmbportnames.TabIndex = 0;
            this.cmbportnames.SelectedIndexChanged += new System.EventHandler(this.cmbportnames_SelectedIndexChanged);
            // 
            // butopencom
            // 
            this.butopencom.Location = new System.Drawing.Point(163, 13);
            this.butopencom.Name = "butopencom";
            this.butopencom.Size = new System.Drawing.Size(125, 23);
            this.butopencom.TabIndex = 1;
            this.butopencom.Text = "Open COM port";
            this.butopencom.UseVisualStyleBackColor = true;
            this.butopencom.Click += new System.EventHandler(this.butopencom_Click);
            // 
            // butclosecom
            // 
            this.butclosecom.Location = new System.Drawing.Point(314, 12);
            this.butclosecom.Name = "butclosecom";
            this.butclosecom.Size = new System.Drawing.Size(115, 23);
            this.butclosecom.TabIndex = 2;
            this.butclosecom.Text = "Close COM port";
            this.butclosecom.UseVisualStyleBackColor = true;
            this.butclosecom.Click += new System.EventHandler(this.butclosecom_Click);
            // 
            // cmdtb1
            // 
            this.cmdtb1.Location = new System.Drawing.Point(12, 81);
            this.cmdtb1.Name = "cmdtb1";
            this.cmdtb1.Size = new System.Drawing.Size(100, 22);
            this.cmdtb1.TabIndex = 4;
            this.cmdtb1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.cmdtb1_KeyDown);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.cmdtb1);
            this.Controls.Add(this.butclosecom);
            this.Controls.Add(this.butopencom);
            this.Controls.Add(this.cmbportnames);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cmbportnames;
        private System.Windows.Forms.Button butopencom;
        private System.Windows.Forms.Button butclosecom;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.TextBox cmdtb1;
    }
}

