using ServicesForTrivia;
using System;
using System.Windows;
using System.Windows.Controls;

namespace GUI_for_trivia
{
    /// <summary>
    /// Interaction logic for SignUpWindow.xaml
    /// </summary>
    public partial class SignUpWindow : Window
    {
        private void HandlerError(string errorMsg)
        {
            error_text.Text = errorMsg;
            error_text.Visibility = Visibility.Visible;
        }
        string username = string.Empty;
        string password = string.Empty;
        string email = string.Empty;
        public SignUpWindow()
        {
            InitializeComponent();
        }

        private void username_text_box_TextChanged(object sender, TextChangedEventArgs e)
        {
            username = username_text_box.Text;
        }

        private void password_text_box_TextChanged(object sender, TextChangedEventArgs e)
        {
            password = password_text_box.Text;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                User user = LoginComunicator.SignUp(username, password, email);
                var win = new RoomsMenu(user);
                win.Show();
                this.Close();
            }
            catch (Exception error)
            {
                HandlerError($"{error.Message}");
            }
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            email = email_text_box.Text;
        }

        private void Hyperlink_Click(object sender, RoutedEventArgs e)
        {
            var loginPage = new MainWindow();
            loginPage.Show();
            this.Close();
        }
    }
}
