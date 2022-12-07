namespace SmallEngine
{
    internal static class Program
    {

        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            ApplicationConfiguration.Initialize();
            Form1 form1 = new Form1();
            Application.Run(form1);
        }
    }
}