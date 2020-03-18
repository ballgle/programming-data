# 极客时间 [《Flutter核心技术与实战》](https://time.geekbang.org/column/article/104040)：依赖管理1-资源管理

一个应用程序主要由两部分内容组成：**代码和资源**。代码关注逻辑功能，而如图片、字符串、字体、配置文件等资源则关注视觉功能。

- 主题样式是从逻辑层面分享应该如何管理资源的配置。
- 图片、字符串、字体、配置文件等资源的管理则是物理层面的。

**资源外部化，即把代码与资源分离，是现代 UI 框架的主流设计理念**。因为这样不仅有利于单独维护资源，还可以对特定设备提供更准确的兼容性支持，使得我们的应用程序可以自动根据实际运行环境来组织视觉功能，适应不同的屏幕大小和密度等。

## 1 资源管理

常见的资源类型包括 `JSON 文件、配置文件、图标、图片以及字体文件`等。在 Android、iOS 平台中，为了区分不同分辨率的手机设备，图片和其他原始资源是区别对待的：

- iOS 使用 Images.xcassets 来管理图片，其他的资源直接拖进工程项目即可；
- Android 的资源管理粒度则更为细致，使用以 drawable+ 分辨率命名的文件夹来分别存放不同分辨率的图片，其他类型的资源也都有各自的存放方式，比如布局文件放在 res/layout 目录下，资源描述文件放在 res/values 目录下，原始文件放在 assets 目录下等。

在 Flutter 中，资源管理则简单得多：**资源（assets）可以是任意类型的文件，比如 JSON 配置文件或是字体文件等，而不仅仅是图片**。我们可以把资源存放在项目中的任意目录下，只需要使用根目录下的 pubspec.yaml 文件，对这些资源的所在位置进行显式声明以帮助 Flutter 识别出这些资源就可以了。

在指定路径名的过程中，我们既可以对每一个文件进行挨个指定，也可以采用子目录批量指定的方式。

### 逐个指定与批量指定

假设项目根目录下的 assets 下有如下资源：

```dart
assets
├── background.jpg
├── icons
│   └── food_icon.jpg
├── loading.gif
└── result.json
```

以下代码分别演示了挨个指定和子目录批量指定这两种方式：

- 通过单个文件声明的，我们需要完整展开资源的相对路径；
- 对于目录批量指定的方式，只需要在目录名后加路径分隔符就可以了：

```yaml
flutter:
  assets:
    - assets/background.jpg   # 挨个指定资源路径
    - assets/loading.gif  # 挨个指定资源路径
    - assets/result.json  # 挨个指定资源路径
    - assets/icons/    # 子目录批量指定
    - assets/ # 根目录也是可以批量指定的
```

注意：**目录批量指定并不递归，只有在该目录下的文件才可以被包括，如果下面还有子目录的话，需要单独声明子目录下的文件**。

### 不同资源的加载

在 Flutter 中，对不同类型的资源文件处理方式略有差异：

- 使用 Image.asset 构造方法完成图片资源的加载及显示。
- 对于其他资源文件的加载，我们可以通过 Flutter 应用的主资源 Bundle 对象 rootBundle，来直接访问。
- 对于字符串文件资源，我们使用 loadString 方法。
- 对于二进制文件资源，则通过 load 方法。

以下代码演示了获取 result.json 文件，并将其打印的过程：

```dart
rootBundle.loadString('assets/result.json').then((msg)=>print(msg));
```

### 像素密度的管理方式

**Flutter 也遵循了基于像素密度的管理方式**：与 Android、iOS 开发类似，Flutter 也遵循了基于像素密度的管理方式，如 1.0x、2.0x、3.0x 或其他任意倍数，Flutter 可以根据当前设备分辨率加载最接近设备像素比例的图片资源。

为了让 Flutter 更好地识别，我们的资源目录应该将 1.0x、2.0x 与 3.0x 的图片资源分开管理。以 background.jpg 图片为例，这张图片位于 assets 目录下。如果想让 Flutter 适配不同的分辨率，我们需要将其他分辨率的图片放到对应的分辨率子目录中，如下所示：

```dart
assets
├── background.jpg    //1.0x 图
├── 2.0x
│   └── background.jpg  //2.0x 图
└── 3.0x
    └── background.jpg  //3.0x 图
```

在 pubspec.yaml 文件声明这个图片资源时，仅声明 1.0x 图资源即可：

```yaml
flutter:
  assets:
    - assets/background.jpg   #1.0x 图资源
```

注意：**即使我们的 App 包没有包含 1.0x 资源，我们仍然需要像上面那样在 pubspec.yaml 中将它显示地声明出来，因为它是资源的标识符**。

#### 资源的加载顺序

1.0x 分辨率的图片是资源标识符，而 Flutter 则会根据实际屏幕像素比例加载相应分辨率的图片。但**如果主资源缺少某个分辨率资源，Flutter 会在剩余的分辨率资源中选择最低的分辨率资源去加载**。

比如：如果我们的 App 包只包括了 2.0x 资源，对于屏幕像素比为 3.0 的设备，则会自动降级读取 2.0x 的资源。

### 字体的加载

在一些特殊的情况下，我们可能需要使用自定义字体来提升视觉体验。在 Flutter 中，使用自定义字体同样需要在 pubspec.yaml 文件中提前声明。需要注意的是，**字体实际上是字符图形的映射。所以，除了正常字体文件外，如果你的应用需要支持粗体和斜体，同样也需要有对应的粗体和斜体字体文件**。

在将 RobotoCondensed 字体摆放至 assets 目录下的 fonts 子目录后，下面的代码演示了如何将支持斜体与粗体的 RobotoCondensed 字体加到我们的应用中：

```yaml
fonts:
  - family: RobotoCondensed  # 字体名字
    fonts:
      - asset: assets/fonts/RobotoCondensed-Regular.ttf # 普通字体
      - asset: assets/fonts/RobotoCondensed-Italic.ttf
        style: italic  # 斜体
      - asset: assets/fonts/RobotoCondensed-Bold.ttf
        weight: 700  # 粗体
```

这些声明其实都对应着 TextStyle 中的样式属性，如：

1. 字体名 family 对应着 fontFamily 属性
2. 斜体 italic 与正常 normal 对应着 style 属性
3. 字体粗细 weight 对应着 fontWeight 属性

在使用时，我们只需要在 TextStyle 中指定对应的字体即可：

```dart
Text("This is RobotoCondensed", style: TextStyle(
    fontFamily: 'RobotoCondensed',// 普通字体
));
Text("This is RobotoCondensed", style: TextStyle(
    fontFamily: 'RobotoCondensed',
    fontWeight: FontWeight.w700, // 粗体
));
Text("This is RobotoCondensed italic", style: TextStyle(
  fontFamily: 'RobotoCondensed',
  fontStyle: FontStyle.italic, // 斜体
));
```

## 2 原生平台的资源设置

 Flutter 启动时依赖的是原生 Android 和 iOS 的运行环境。上面介绍的资源管理机制其实都是在 Flutter 应用内的，而在 Flutter 框架运行之前，我们是没有办法访问这些资源的。

Flutter 需要原生环境才能运行，但是**有些资源我们需要在 Flutter 框架运行之前提前使用，比如要给应用添加图标，或是希望在等待 Flutter 框架启动时添加启动图，我们就需要在对应的原生工程中完成相应的配置**。

如何更换 App 启动图标：

- 对于 Android 平台，启动图标位于根目录 android/app/src/main/res/mipmap 下。
- 对于 iOS 平台，启动图位于根目录 ios/Runner/Assets.xcassets/AppIcon.appiconset 下。

更换启动图：

- 对于 Android 平台，启动图位于根目录 android/app/src/main/res/drawable 下，是一个名为 launch_background 的 XML 界面描述文件。
- 对于 iOS 平台，启动图位于根目录 ios/Runner/Assets.xcassets/LaunchImage.imageset 下。

## 3 思考题

1.如果我们只提供了 1.0x 与 2.0x 的资源图片，对于像素密度为 3.0 的设备，Flutter 会自动降级到哪套资源？

- Flutter 会选择 2.0 的资源图片，优先使用和当前像素密度相近的资源。

2.如果我们只提供了 2.0x 的资源图片，对于像素密度为 1.0 的设备，Flutter 会如何处理呢？

- 找 2.0x 图片，按分辨率由低到高找，但是会自动进行压缩处理。
