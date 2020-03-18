import 'package:flutter/material.dart';

Widget buildHorizontalListView() =>
    Scaffold(
      appBar: new AppBar(
        title: new Text('Horizontal List'),
      ),

      body: new Container(
        margin: new EdgeInsets.symmetric(vertical: 20.0),
        height: 200.0,

        child: new ListView(
          scrollDirection: Axis.horizontal,

          children: <Widget>[
            new Container(
              width: 160.0,
              color: Colors.red,
            ),
            new Container(
              width: 160.0,
              color: Colors.blue,
            ),
            new Container(
              width: 160.0,
              color: Colors.green,
            ),
            new Container(
              width: 160.0,
              color: Colors.yellow,
            ),
            new Container(
              width: 160.0,
              color: Colors.orange,
            ),
          ],

        ),
      ),
    );
