# eve-video-attendance

## 开发

需要先安装vcpkg，通过vcpkg安装tesseract，安装并配置vs工程可使用：

```cmd
// 直接安装tesseract是X86的，不支持X64的，根据实际情况自行安装。
vcpkg install tesseract:x64-windows
```

opencv我是根据opencv[官方文档](https://docs.opencv.org/4.6.0/dd/d6e/tutorial_windows_visual_studio_opencv.html)进行设置的，没通过vcpkg安装。

## 目录说明

vs-project 是vs工程，vs打开vs-project\vs-project.sln打开工程。

vs-project\eve-video-attendance-setup-project 是工程setup程序打包配置。

vs-project\tessdata  内含tesseract 中文识别模型库