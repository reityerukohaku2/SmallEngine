using Vortice.DXGI;
using Vortice.Direct3D;
using Vortice.Direct3D11;
using System.Windows.Forms;
using SharpGen;
using SharpGen.Runtime;
using static Vortice.Direct3D11.D3D11;
using static Vortice.DXGI.DXGI;

namespace SmallEngine
{
    internal class Direct3DMain
    {
        // よくわかんねぇけど、適当に宣言してみっか…ｗ
        // ここ見ながら書いてる https://gamesgard.com/directx11_lesson02/

        /// <summary>
        /// デフォルト画面横サイズ(あとで2Dベクトルのクラスに置き換える)
        /// </summary>
        public static readonly int DEFAULT_WIDTH = 1920;

        /// <summary>
        /// デフォルト画面縦サイズ(あとで2Dベクトルのクラスに置き換える)
        /// </summary>
        public static readonly int DEFAULT_HEIGHT = 1080;


        private IDeviceContext deviceContext;
        private IDXGIFactory factory;
        private IDXGISwapChain swapChain;
        private RenderTargetViewDescription backBuffer;

        public Direct3DMain(IntPtr HWND) : this(HWND, DEFAULT_WIDTH, DEFAULT_HEIGHT)
        {
        }

        /// <summary>
        /// 画面描画用のクラスのコンストラクタです
        /// </summary>
        /// <param name="HWND">ウィンドウハンドル</param>
        /// <param name="width">画面横サイズ</param>
        /// <param name="height">画面縦サイズ</param>
        public Direct3DMain(IntPtr HWND, int width, int height)
        {
            //=====================================================================================================
            // 参照デバイスを作成するの項目を参照してください
            // https://learn.microsoft.com/ja-jp/windows/win32/direct3d11/overviews-direct3d-11-devices-create-ref
            //=====================================================================================================

            // スワップチェインの初期値を定義
            // よくわからんパラメータがいっぱいある
            SwapChainDescription dec = new SwapChainDescription();
            dec.BufferCount = 1;                                    // わからん。
            dec.BufferDescription.Width = width;
            dec.BufferDescription.Height = height;
            dec.BufferDescription.Format = Format.R8G8B8A8_UNorm;   // カラーフォーマットかな
            dec.BufferDescription.RefreshRate.Numerator = 60;
            dec.BufferDescription.RefreshRate.Denominator = 1;
            dec.BufferUsage = Usage.RenderTargetOutput;             // 何にこのスワップチェインを使うのかってこと？
            dec.OutputWindow = HWND;
            dec.SampleDescription.Count = 1;
            dec.SampleDescription.Quality = 0;
            dec.Windowed = true;

            // DirectXの要求レベル(今回は11.0)
            FeatureLevel? featureLevel = FeatureLevel.Level_11_0;
            FeatureLevel[] featureLevels = new FeatureLevel[] { FeatureLevel.Level_11_0 };

            // デバイスとスワップチェインの作成(このメソッド見つけるのに苦労した)
            // 
            Result result = Result.Ok;
            IDXGISwapChain swapChain;
            ID3D11Device device;
            ID3D11DeviceContext deviceContext;
            if (Result.Fail == (result = D3D11CreateDeviceAndSwapChain(
                // いっぱい引数を渡しましょう
                null,
                DriverType.Reference,
                0,
                featureLevels,
                dec,
                out swapChain,
                out device,
                out featureLevel,
                out deviceContext
                )))
            {
                
            }
        }
    }
}
