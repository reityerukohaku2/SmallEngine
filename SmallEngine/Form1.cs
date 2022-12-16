using Vortice.DXGI;
using Vortice.Direct3D11;
using System.Windows.Interop;

namespace SmallEngine
{
    public partial class Form1 : Form
    {
        private Direct3DMain d3dMain;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            d3dMain = new Direct3DMain(Handle);
            while (true)
            {
                Application.DoEvents();

                float[] color = new float[4] { 0.2f, 0.2f, 1.0f, 1.0f };

                d3dMain.deviceContext.ClearRenderTargetView(d3dMain.backBufferView, new Vortice.Mathematics.Color(0.2f, 0.2f, 1.0f));
                d3dMain.swapChain.Present(1, 0);
            }
        }
    }
}