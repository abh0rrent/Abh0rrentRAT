namespace RATServer
{
    partial class Abh0rrentServer
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            button4 = new Button();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            label1 = new Label();
            button5 = new Button();
            textBox4 = new TextBox();
            button6 = new Button();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(73, 80);
            button1.Name = "button1";
            button1.Size = new Size(105, 23);
            button1.TabIndex = 0;
            button1.Text = "Start Server";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_ClickAsync;
            // 
            // button2
            // 
            button2.BackColor = SystemColors.ButtonHighlight;
            button2.Location = new Point(73, 159);
            button2.Name = "button2";
            button2.Size = new Size(105, 23);
            button2.TabIndex = 1;
            button2.Text = "Send Command";
            button2.UseVisualStyleBackColor = false;
            button2.Click += button2_Click;
            // 
            // button3
            // 
            button3.Location = new Point(73, 283);
            button3.Name = "button3";
            button3.Size = new Size(105, 23);
            button3.TabIndex = 2;
            button3.Text = "Start Shell";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button4
            // 
            button4.Location = new Point(73, 328);
            button4.Name = "button4";
            button4.Size = new Size(105, 23);
            button4.TabIndex = 3;
            button4.Text = "Close Server";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(12, 51);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(105, 23);
            textBox1.TabIndex = 4;
            textBox1.Text = "IP Address";
            textBox1.TextChanged += textBox1_TextChanged;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(129, 51);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(105, 23);
            textBox2.TabIndex = 5;
            textBox2.Text = "Port";
            textBox2.TextChanged += textBox2_TextChanged;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(12, 130);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(105, 23);
            textBox3.TabIndex = 6;
            textBox3.Text = "Single Command";
            textBox3.TextChanged += textBox3_TextChanged;
            // 
            // label1
            // 
            label1.BackColor = SystemColors.ActiveCaptionText;
            label1.ForeColor = SystemColors.ControlLightLight;
            label1.ImageAlign = ContentAlignment.TopLeft;
            label1.Location = new Point(240, 30);
            label1.Name = "label1";
            label1.Size = new Size(500, 400);
            label1.TabIndex = 7;
            label1.Click += label1_Click;
            // 
            // button5
            // 
            button5.Location = new Point(73, 373);
            button5.Name = "button5";
            button5.Size = new Size(105, 23);
            button5.TabIndex = 8;
            button5.Text = "Exit";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // textBox4
            // 
            textBox4.Location = new Point(12, 208);
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(105, 23);
            textBox4.TabIndex = 9;
            textBox4.Text = "Full File Path";
            textBox4.TextChanged += textBox4_TextChanged;
            // 
            // button6
            // 
            button6.Location = new Point(73, 237);
            button6.Name = "button6";
            button6.Size = new Size(105, 23);
            button6.TabIndex = 10;
            button6.Text = "Upload";
            button6.UseVisualStyleBackColor = true;
            button6.Click += button6_Click;
            // 
            // Abh0rrentServer
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.ControlDarkDark;
            ClientSize = new Size(784, 461);
            Controls.Add(button6);
            Controls.Add(textBox4);
            Controls.Add(button5);
            Controls.Add(label1);
            Controls.Add(textBox3);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Controls.Add(button4);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(button1);
            Name = "Abh0rrentServer";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private Button button2;
        private Button button3;
        private Button button4;
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private Label label1;
        private Button button5;
        private TextBox textBox4;
        private Button button6;
    }
}
