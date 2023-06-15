using ServicesForTrivia;
using System;
using System.Windows;
using System.Windows.Controls;

namespace GUI_for_trivia
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private void HandlerError(string errorMsg)
        {
            error_text.Text = errorMsg;
            error_text.Visibility = Visibility.Visible;
            Console.WriteLine(errorMsg);
        }
        string username = string.Empty;
        string password = string.Empty;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            username = username_text_box.Text;
        }

        private void password_text_box_TextChanged(object sender, TextChangedEventArgs e)
        {
            password = password_text_box.Text;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            error_text.Text = string.Empty;
            error_text.Visibility = Visibility.Hidden;
            try
            {
                User user = LoginComunicator.Login(username, password);
                var win = new RoomsMenu(user);
                win.Show();
                this.Close();
            }
            catch (Exception error)
            {
                HandlerError($"error: {error.Message}");
            }
            
        }

        private void Hyperlink_Click(object sender, RoutedEventArgs e)
        {
            var SignUp = new SignUpWindow();
            SignUp.Show();
            this.Close();
        }

        
    }
}
