import 'package:flutter/material.dart';

Widget buildCustomScrollView() =>
    Material(
      child: CustomScrollView(
        slivers: <Widget>[

          //AppBar，包含一个导航栏
          SliverAppBar(
            pinned: true,
            expandedHeight: 250.0,
            flexibleSpace: FlexibleSpaceBar(
              title: const Text('Demo'),
              background: Image.asset(
                "./images/lake.jpg", fit: BoxFit.cover,),
            ),
          ),

          new SliverGrid( //Grid
            gridDelegate: new SliverGridDelegateWithFixedCrossAxisCount(
              crossAxisCount: 2, //Grid按两列显示
              mainAxisSpacing: 10.0,
              crossAxisSpacing: 10.0,
              childAspectRatio: 4.0,
            ),
            delegate: new SliverChildBuilderDelegate(
                  (BuildContext context, int index) {
                //创建子widget
                return new Container(
                  alignment: Alignment.center,
                  color: Colors.cyan[100 * (index % 9)],
                  child: new Text('grid item $index'),
                );
              },
              childCount: 20,
            ),
          ),

          /*
          SliverPadding、SliverAppBar等是和可滚动Widget无关的，
          它们主要是为了结合CustomScrollView一起使用，这是因为CustomScrollView的子widget必须都是Sliver。
          SliverPadding(
              padding: const EdgeInsets.all(8.0),
          ),
          */

          //List
          new SliverFixedExtentList(
            itemExtent: 50.0,
            delegate: new SliverChildBuilderDelegate(
                    (BuildContext context, int index) {
                  //创建列表项
                  return new Container(
                    alignment: Alignment.center,
                    color: Colors.lightBlue[100 * (index % 9)],
                    child: new Text('list item $index'),
                  );
                },
                childCount: 50 //50个列表项
            ),
          ),

        ],
      ),
    );
