# [慕课网实战\Socket网络编程进阶与实战](https://coding.imooc.com/down/286.html) 代码

代码列表：

## 1、**l2-l6**：BIO 数据传输演示

- l2：模拟服务端和客户端
- l3：upd API 示例
- l4：tcp API 示例
- l5：tcp udp 配合示例
- l6：建议聊天室

## 2、 **l7**：NIO 改写服务器

- l7-01-nio-server：使用 NIO 重写服务器
- l7-02-clink-api：根据NIO，定义一套 Socket 通讯 API
  - `clink.core.IoContext`：整套 API 的上下文，用于启动框架。
  - `clink.core.IoArgs`：IO读写参数，进行读或写时，用 IoArgs 来承载数据，内部封装的时 ByteBuffer。
  - `clink.core.Sender`：定义了数据发送功能，发送的是 IoArgs。
  - `clink.core.Receiver`：定义了数据接收功能，通过 IoArgs 来接收数据。
  - `clink.impl.SocketChannelAdapter`：实现了 Sender, Receiver, 即使用 SocketChannel 来实现 Sender, Receiver 定义的数据读写功能。
  - `clink.core.Connector`：代表一个 SocketChannel 连接，创建时需要一个代表客户端的 SocketChannel，然后内部实例化 SocketChannelAdapter，用于调用 Sender 和  Receiver 执行读写操作。
  - `clink.core.IoProvider`：IO 读写调度器，可以把关心可读/可写 的 SocketChannel 注册给 IoProvider ，当可读/可写时，对应的回调将会被调用，每一次读写回调后，需要重新注册读写事件。
  - `clink.impl.IoSelectorProvider`：是 IoProvider 的实现者，内部使用 Selector 来实现非阻塞的 IO 调度。

## 3、**l8**：复现粘包，消息不完整的问题

- l8-q1：模拟同一个消息反复收到消息到达回调，修改类
  - IoSelectorProvider：注释了 selectionKey.interestOps(selectionKey.readyOps() & ~keyOps); 
  - SocketChannelAdapter：mHandleInputCallback 中延迟处理消息
- l8-q2：模拟消息粘包的问题，修改类
  - TCPClient：客户端连续发送四条消息，服务器将其当作一条消息处理。
- l8-q3：模拟单消息不完整问题，修改类
  - IoArgs 容量改为 4 个字节，模拟单消息不完整问题

## 4、chat-room-v1-bytes：为了解决丢包和粘包问题

为了解决丢包和粘包问题，需要

- 对数据包进行分析与特征提取。
- 构建数据头，用于包的拆分和再组装。
- 处理好数据头、数据体接收。

### 类的功能与职责

提出 Packet 概念，一个 Packet 代表一个完整的消息：

- `clink.core.Packet`：公共的数据封装（消息类型，消息长度），提供了类型以及数据长度的定义。
- `clink.core.SendPacket`：公发送包的定义
- `clink.core.ReceivePacket`：接收包的定义，不同的数据类型对应不同的 ReceivePack 实现。
- `clink.box.StringReceivePacket`：字符串接收包。
- `clink.box.StringSendPacket`：字符串发送包。

Connector：代表一个 Socket 连接，其主要工作如下：

- Connector 的创建需要一个 SocketChannel。
- 通过 SocketChannel 实例化  SocketChannelAdapter。SocketChannelAdapter 是 Sender 和 Receiver 的实现者，具有发送和接收数据功能。
- 通过 Sender 创建发送调度则 SendDispatcher。
- 通过 Receiver 创建接收调度则  ReceiveDispatcher

数据的接受和发送流程：

- IoProvider 负责具体的调度，内部有两个 Selector，分别用于选择可读和可写的 Channel。
- Sender 和 Receiver 的实现者 SocketChannelAdapter 向 IoProvider 注册可读可写回调。
- 当可读或者可写时，IoProvider 通过回到回调通知到 SocketChannelAdapter，即 Sender 和 Receiver。

String 的接收和发送：

- 接收 String：接受到的是 StringReceivePacket，然后解析为 String。
- 发送 String：通过将 String 封装为 StringSendPacket 进行发送。

SendDispatcher，发送调度器：

- SendDispatcher 负责发送的调度，调用 Sender 的进行数据发送。
- SendDispatcher 主要职责是：维护发送包的队列；对每个包进行拆分发送。
- SendDispatcher 的实现者是 AsyncSendDispatcher

ReceiveDispatcher，发送调度器：

- ReceiveDispatcher 负责接收数据的调度，调用 Receiver 的进行数据接收。
- ReceiveDispatcher 主要职责是：在接受数据的过程中，按照头部信息将数据组装成一个完整的包。
- ReceiveDispatcher 的实现者是 AsyncReceiveDispatcher

IoArgs：

- 发送和接收数据的载体，内部维护者一个 ByteBuffer。
- 从 Channel 读取数据到自身，将自身的数据写入到 Channel。

## 5、chat-room-v2-stream：将基于 bytes 的传输方法改为 stream 传输

调整：

- Packet 改成流传输
- IoArgs 支持流的读写

### Packet 类的调整

Packet 改成了基于 Stream 传输数据。

```log
Packet (clink.core)
    |--SendPacket (clink.core)
    |       |--BytesSendPacket (clink.box)
    |       |       |--StringSendPacket (clink.box)
    |       |--FileSendPacket (clink.box)
    |--ReceivePacket (clink.core)
    |       |--AbsByteArrayReceivePacket (clink.box)
    |       |       |--StringReceivePacket (clink.box)
    |       |       |--BytesReceivePacket (clink.box)
    |       |--FileReceivePacket (clink.box)
```

- `Packet<Stream extends Closeable>`：基于 Stream 的 Packet，不同的 Packet 对应不同 Stream。
- `SendPacket<Stream extends InputStream> extends Packet<Stream>`：发送包基于 InputStream。
- `BytesSendPacket extends SendPacket<ByteArrayInputStream>`：基于 ByteArrayInputStream 的发送包，主要用于可直接加载到内存的小数据传输。
- `StringSendPacket extends BytesSendPacket`：String 发送时直接转换为字节进行发送。
- `FileSendPacket extends SendPacket<FileInputStream>`：文件则通过文件流进行发送。
- `ReceivePacket<Stream extends OutputStream, Entity> extends Packet<Stream>`：接收包基于 OutputStream，Entity 消息的最终表现类型，比如文件、字符串。
- `AbsByteArrayReceivePacket<Entity> extends ReceivePacket<ByteArrayOutputStream, Entity>`：定义最基础的基于 ByteArrayOutputStream 的输出接收包
- `StringReceivePacket extends AbsByteArrayReceivePacket<String>`：String 也是通过读取字节进行接受的。
- `BytesReceivePacket extends AbsByteArrayReceivePacket<byte[]>`：纯 byte 数组接收包。
- `FileReceivePacket extends ReceivePacket<FileOutputStream, File>`：文件接收包，通过 FileOutputStream 接收文件。

### IoArgs 类的调整

```java
    //读或写准备就绪的回调，每一次读或者写的都会先调用 {@link #onStarted(IoArgs)}，单词读写完成，则调用 {@link #onCompleted(IoArgs)}。
    public interface IoArgsEventListener {
        void onStarted(IoArgs args);

        void onCompleted(IoArgs args);
    }

    //IoArgs 提供者、处理者；数据的生产或消费者。定义为这种形式，用于异步处理IO。
    public interface IoArgsEventProcessor {

        //提供一份可消费的IoArgs
        IoArgs provideIoArgs();

        //消费失败时回调
        void consumeFailed(IoArgs ioArgs, Exception e);

        //消费成功
        void onConsumeCompleted(IoArgs args);
    }
```

IoArgs 中的 IoArgsEventListener 调整为 IoArgsEventProcessor，调整之后有两个好处：

- 可以处理消费 IoArgs 失败的情况。
- 延迟了 IoArgs 对数据的读取（只在可写的情况下才去填充 IoArgs）。