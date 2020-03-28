# 包管理

---
## 1 rpm与yum

rpm由RedHat公司开发，Fedora、CentOS、SuSe等Linux发行版使用其管理软件安装。yum是基于rpm的在线升级机制。

---
## 2 dpkg与apt

dpkg机制最早由DebianLinux社区开发出来，派生于Debian的Linux发行版本大多使用dpkg这个机制来管理软件，比如ubantu、B2D等。apt是基于dpkg的在线升级机制。

---
## 3 apt使用

### 配置源

    首先备份原始的文件
    sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup
    配置镜像
    https://mirrors.tuna.tsinghua.edu.cn/  //清华大学的镜像
    选择好对应的平台和版本，覆盖/etc/apt/sources.list中的文件即可

    spt-get常用命令：
    sudo apt-get update  更新源
    sudo apt-get install package 安装包
    sudo apt-get remove package 删除包
    sudo apt-cache search package 搜索软件包
    sudo apt-cache show package  获取包的相关信息，如说明、大小、版本等
    sudo apt-get install package --reinstall   重新安装包
    sudo apt-get -f install   修复安装
    sudo apt-get remove package --purge 删除包，包括配置文件等
    sudo apt-get build-dep package 安装相关的编译环境
    sudo apt-get upgrade 更新已安装的包
    sudo apt-get dist-upgrade 升级系统
    sudo apt-cache depends package 了解使用该包依赖那些包
    sudo apt-cache rdepends package 查看该包被哪些包依赖
    sudo apt-get source package  下载该包的源代码
    sudo apt-get clean && sudo apt-get autoclean 清理无用的包
    sudo apt-get check 检查是否有损坏的依赖

---
## 4 软件安装位置

apt-get 下载后，软件所在路径是什么：`/var/cache/apt/archives`

ubuntu 默认的PATH为：`PATH=/home/brightman/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games`

**apt-get install安装目录是包的维护者确定的，不是用户**

`dpkg -L +软件包的名字`，获取这个软件包包含了哪些文件

```
系统安装软件一般在/usr/share，可执行的文件在/usr/bin，配置文件可能安装到了/etc下等。
文档一般在 /usr/share
可执行文件 /usr/bin
配置文件 /etc
lib文件 /usr/lib
```

---
## 5 wget下载软件

使用wget可以下载软件，然后手动解压。

---
## 引用

- [Ubuntu(Debian)的aptitude与apt-get的区别和联系](http://www.cnblogs.com/yuxc/archive/2012/08/02/2620003.html)
