# 极客时间 [《Flutter核心技术与实战》](https://time.geekbang.org/column/article/104040)：Flutter国际化

如果我们想为全世界的使用者提供统一而标准的体验，那么首先就需要让 App 能够支持多种语言。而这一过程，一般被称为“国际化”。但国际化并不只是语言的翻译，**更为准确地描述国际化的工作职责，应该是“涉及语言及地区差异的适配改造过程”**。比如：

1. 如果我们要显示金额，同样的面值，在中国会显示为￥100，而在美国则会显示为 $100。
2. App 的引导图，在中国我们可能会选用长城作为背景，而在美国我们则可能会选择金门大桥作为背景。

可以看出，一款 App 的国际化的具体过程包括对`文案翻译、货币单位、背景图片`资源的配置工作。因此，为了做好国际化工作，我们在设计 App 架构时，需要提前将语言与地区的差异部分独立出来。

## 1 LocalizationsDelegate

在 Flutter 中，国际化的语言和地区的差异性配置，是应用程序代码的一部分。如果要在 Flutter 中实现文本的国际化，我们需要执行以下几步：

1. 首先，实现一个 LocalizationsDelegate（即翻译代理），并将所有需要翻译的文案全部声明为它的属性；
2. 然后，依次为需要支持的语言地区进行手动翻译适配；
3. 最后，在应用程序 MaterialApp 初始化时，将这个代理类设置为应用程序的翻译回调。

如果我们中途想要新增或者删除某个语系或者文案，都需要修改程序代码。可以看到，如果我们想要使用官方提供的国际化方案来设计 App 架构，不仅工作量大、繁琐，而且极易出错。所以一般不推荐单纯使用这种方案。

## 2 Flutter i18n 插件

Flutter i18n 是 Android Studio 中的一个插件，这个插件在其内部提供了不同语言地区的配置封装，能够帮助我们自动地从翻译稿生成 Dart 代码。

安装和使用 Flutter i18n 插件：

1. AndroidStudio 插件仓库中搜索并安装 `Flutter i18n` 插件。
2. Flutter i18n 依赖 flutter_localizations 插件包，所以我们还需要在 pubspec.yaml 文件里。

```yaml
dependencies:
  flutter_localizations:
    sdk: flutter
```

安装配置完之后，会发现在 res 文件夹下，自动多了一个 `values/strings_en.arb` 的文件。arb 文件是 JSON 格式的配置，用来存放文案标识符和文案翻译的键值对：

```json
{
    "app_title":"Flutter国际化"
}
```

我们只要修改了 `res/values` 下的 arb 文件，i18n 插件就会自动帮我们生成对应的代码。`strings_en` 文件，则是系统默认的英文资源配置。为了支持中文，我们还需要在 values 目录下再增加一个 `strings_zh.arb` 文件。

修改一下 strings_zh.arb 文件，可以看到，Flutter i18n 插件会为我们自动生成 generated/i18n.dart。这个类中不仅以资源标识符属性的方式提供了静态文案的翻译映射，对于通过参数来实现动态文案的 message_tip 标识符，也自动生成了一个同名内联函数。

## 3 国际化案例

以 Flutter 官方的工程模板，即计数器 demo 来演示如何在 Flutter 中实现国际化。参考下面代码:

```dart
// 应用程序入口
class MyApp extends StatelessWidget {

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
    //翻译回调
      localizationsDelegates: const [
        S.delegate,// 应用程序的翻译回调
        GlobalMaterialLocalizations.delegate,//Material 组件的翻译回调
        GlobalWidgetsLocalizations.delegate,// 普通 Widget 的翻译回调
      ],
    //设置支持的语系
      supportedLocales: S.delegate.supportedLocales,// 支持语系
      //title 的国际化回调：提取翻译文案的代码需要在能获取到翻译上下文的前提下才能生效，也就是说只能针对 MaterialApp 的子 Widget 生效。
      onGenerateTitle: (context){
        return S.of(context).app_title;
      },
      home: MyHomePage(),
    );
  }

}
```

1. 在应用程序的入口，即 MaterialApp 初始化时，为其设置了支持国际化的两个重要参数，即 localizationsDelegates 与 supportedLocales。前者为应用的翻译回调，而后者则为应用所支持的语言地区属性。
2. S.delegate 是 Flutter i18n 插件自动生成的类，包含了所支持的语言地区属性，以及对应的文案翻译映射。
3. 理论上，通过 S.delegate 就可以完全实现应用的国际化，但为什么我们在配置应用程序的翻译回调时，除了它之外，还加入了 `GlobalMaterialLocalizations.delegate` 与 `GlobalWidgetsLocalizations.delegate` 这两个回调呢？因为 Flutter 提供的 Widget，其本身已经支持了国际化，所以我们没必要再翻译一遍，直接用官方的就可以了，而这两个类则就是官方所提供的翻译回调。我们在 pubspec.yaml 文件中声明的 flutter_localizations 插件包，就是 Flutter 提供的翻译套装，而这两个类就是套装中的著名成员。

应用的主界面文案的国际化，则相对简单得多了，直接通过 S.of(context) 方法就可以拿到 arb 声明的翻译文案了：

```dart
Widget build(BuildContext context) {
  return Scaffold(
    // 获取 appBar title 的翻译文案
    appBar: AppBar(
      title: Text(S.of(context).main_title),
    ),
    body: Center(
      // 传入 _counter 参数，获取计数器动态文案
      child: Text(
        S.of(context).message_tip(_counter.toString())
          )
    ),
    floatingActionButton: FloatingActionButton(
      onPressed: _incrementCounter,// 点击回调
      tooltip: 'Increment',
      child: Icon(Icons.add),
    ),
  );
}
```

**IOS 工程需要额外配置**：由于 iOS 应用程序有一套自建的语言环境管理机制，默认是英文。为了让 iOS 应用正确地支持国际化，我们还需要在原生的 iOS 工程中进行额外的配置。打开 iOS 原生工程，切换到工程面板。在 Localization 这一项配置中，可以看到 iOS 工程已经默认支持了英文，所以还需要点击“+”按钮，新增中文，之后就完成了 iOS 工程的国际化配置。

## 4 原生工程配置

上面介绍的国际化方案，其实都是在 Flutter 应用内实现的。而在 Flutter 框架运行之前，我们是无法访问这些国际化文案的。Flutter 需要原生环境才能运行，但有些文案，比如应用的名称，我们需要在 Flutter 框架运行之前就为它提供多个语言版本（比如英文版本为 computer，中文版本为计数器），这时就需要在对应的原生工程中完成相应的国际化配置了。

## 5 总结

国际化的核心就是语言差异配置抽取。在原生 Android 和 iOS 系统中进行国际化适配，我们只需为需要国际化的资源（比如，字符串文本、图片、布局等）提供不同的文件夹目录，就可以在应用层代码访问国际化资源时，自动根据语言地区进行适配。

但，Flutter 的国际化能力就相对原始很多，不同语言和地区的国际化资源既没有存放在单独的 xml 或者 JSON 上，也没有存放在不同的语言和地区文件夹中。幸好有 Flutter i18n 插件的帮助，否则为一个应用提供国际化的支持将会是件极其繁琐的事情。

## 6 相关示例

- [32_i18n_demo](https://github.com/cyndibaby905/32_i18n_demo)

## 7 思考题

在 Flutter 中，如何实现图片类资源的国际化呢？
