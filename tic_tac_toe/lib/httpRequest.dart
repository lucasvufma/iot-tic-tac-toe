import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'package:http/http.dart' as http;
import 'iotPage.dart';

Future<http.Response> postRequest (data,url) async {
  
  Map map = {
    '$data': 'TRUE'
  };
  //encode Map to JSON
  var body = json.encode(map);
  
  print('$body');

  var response = await http.post(url,
      headers: {"Content-Type": "application/json"},
      body: body
  );
  print('$map');
  //print("${response.statusCode}");
  //print("${response.body}");
  return response;
}