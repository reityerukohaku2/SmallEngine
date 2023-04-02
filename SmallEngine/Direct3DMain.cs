using Vortice.DXGI;
using Vortice.Direct3D;
using Vortice.Direct3D11;
using System.Windows.Forms;
using SharpGen;
using SharpGen.Runtime;
using static Vortice.Direct3D11.D3D11;
using static Vortice.DXGI.DXGI;
using Vortice.Mathematics;

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


        public ID3D11DeviceContext deviceContext;
        public IDXGIFactory factory { get; private set; }
        public IDXGISwapChain swapChain { get; private set; }
        public ID3D11Texture2D backBuffer { get; private set; }
        public ID3D11RenderTargetView backBufferView { get; private set; }
        public ID3D11Device device;

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
            // スワップチェインは、絵が書き込まれるバックバッファ(裏画面)をウィンドウ(表画面)に反映する仕事をする。
            // よくわからんパラメータがいっぱいある
            SwapChainDescription scDec = new SwapChainDescription();
            scDec.BufferCount = 2;                                    // わからん。
            scDec.BufferDescription.Width = width;
            scDec.BufferDescription.Height = height;
            scDec.BufferDescription.Format = Format.R8G8B8A8_UNorm;   // カラーフォーマットかな
            scDec.BufferDescription.RefreshRate.Numerator = 60;
            scDec.BufferDescription.RefreshRate.Denominator = 1;
            scDec.BufferUsage = Usage.RenderTargetOutput;             // 何にこのスワップチェインを使うのかってこと？
            scDec.OutputWindow = HWND;
            scDec.SampleDescription.Count = 1;
            scDec.SampleDescription.Quality = 0;
            scDec.Windowed = true;
            scDec.SwapEffect = SwapEffect.Discard;
            scDec.Flags = SwapChainFlags.AllowModeSwitch;

            // DirectXの要求レベル(今回は11.0)
            FeatureLevel? featureLevel = FeatureLevel.Level_11_0;
            FeatureLevel[] featureLevels = new FeatureLevel[] { FeatureLevel.Level_11_0 };

            // ファクトリー作成
            IDXGIFactory1 factory;
            CreateDXGIFactory1(out factory);

            List<IDXGIAdapter> adapters = new List<IDXGIAdapter>();
            IDXGIAdapter adapter;
            for(int i = 0; factory.EnumAdapters(i, out adapter) == Result.Ok ; i++)
            {
                adapters.Add(adapter);
            }

            // デバイスとデバイスコンテキストの作成
            D3D11CreateDevice(
                adapters.First(),
                DriverType.Unknown,
                DeviceCreationFlags.Debug,
                featureLevels,
                out device,
                out deviceContext
                );

            // スワップチェインの作成(このメソッド見つけるのに苦労した)
            // デバイス：描画する素材(絵とかポリゴン)作るやつ
            // デバイスコンテキスト：デバイスが作った素材をbackbufferに書き込むやつ
            Result result;
            swapChain = factory.CreateSwapChain(device, scDec);

            // スワップチェインからバックバッファを取得
            backBuffer = swapChain.GetBuffer<ID3D11Texture2D>(0);

            // バックバッファ描画用のRenderTargetViewを作成
            RenderTargetViewDescription rtvDec = new RenderTargetViewDescription();
            rtvDec.Format = scDec.BufferDescription.Format;
            rtvDec.ViewDimension = RenderTargetViewDimension.Texture2D;
            backBufferView = device.CreateRenderTargetView(backBuffer, rtvDec);

            // デバイスコンテキストの設定
            // バックバッファをRTとしてセット
            deviceContext.OMSetRenderTargets(backBufferView, null);

            // ビューポート設定
            Viewport vp = new Viewport(0, 0, width, height, 0, 1);
            deviceContext.RSSetViewport(vp);
        }

        void CreateCommandList()
        {
            
        }
        
    }
}
