using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Algorithms
{ 
  /// <summary>
  /// Interaction logic for MainWindow.xaml
  /// </summary>
  public partial class MainWindow : Window
  {
    //public TextBlock Block;

    public MainWindow()
    {
      InitializeComponent();
      SetReferences();
      
    }
    
    void SetReferences()
    {
      //Block = (TextBlock)FindName("Messages");
    }

    public int Booped = 1;

    private void Boop(object sender, RoutedEventArgs e)
    {
      Messages.Text = "Booped " + Booped++;
    }
  }
}
