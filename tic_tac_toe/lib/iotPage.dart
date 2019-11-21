import 'package:flutter/material.dart';
import 'package:tic_tac_toe/game.dart';
import 'globalUrl.dart' as globals;
import 'httpRequest.dart' as http;

class IotPage extends StatelessWidget {
  final _formKey = GlobalKey<FormState>();
  String _ipAdress;

  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return Form(
      key: _formKey,
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.center,
        children: <Widget>[
          Column(children: <Widget>[
            Text(
              'Current Requesting To ',
              style: TextStyle(fontSize: 30.0),
            ),
            Text(globals.url,
                style: TextStyle(
                    fontSize: 25.0,
                    color: Color.fromARGB(255, 217, 35, 50),
                    fontWeight: FontWeight.bold))
          ]),
          Padding(
            padding: const EdgeInsets.only(
              left: 20,
              top: 130,
              right: 20,
              bottom: 5,
            ),
            child: Container(
              width: 500.0,
              height: 250.0,
              child: Material(
                elevation: 20.0,
                shadowColor: Colors.blue,
                child: Column(
                  children: <Widget>[
                    Padding(
                      padding: const EdgeInsets.only(
                        left: 20,
                        top: 15,
                        right: 20,
                        bottom: 5,
                      ),
                      child: TextFormField(
                        decoration: InputDecoration(
                            labelText: 'Url to IOT device request'),
                        validator: (value) {
                          if (value.isEmpty) {
                            return 'Please enter some text';
                          }
                          return null;
                        },
                        onSaved: (value) => _ipAdress = value,
                      ),
                    ),
                    Padding(
                      padding: const EdgeInsets.only(
                        left: 40,
                        top: 20,
                        right: 40,
                        bottom: 2,
                      ),
                      child: MaterialButton(
                        padding: const EdgeInsets.all(8.0),
                        minWidth: 300,
                        textColor: Colors.white,
                        color: Color.fromARGB(255, 4, 104, 191),
                        onPressed: () {
                          // Validate will return true if the form is valid, or false if
                          // the form is invalid.
                          if (_formKey.currentState.validate()) {
                            // Process data.
                            _formKey.currentState.save();
                            globals.url = _ipAdress;
                          }
                        },
                        child: Text('Submit', style: TextStyle(fontSize: 20.0)),
                      ),
                    ),
                    Padding(
                      padding: const EdgeInsets.only(
                        left: 40,
                        top: 2,
                        right: 40,
                        bottom: 2,
                      ),
                      child: MaterialButton(
                        padding: const EdgeInsets.all(2.0),
                        minWidth: 300,
                        textColor: Colors.white,
                        color: Color.fromARGB(255, 217, 35, 50),
                        onPressed: () {
                          // Validate will return true if the form is valid, or false if
                          // the form is invalid.
                          http.postRequest("RESET", globals.url);
                        },
                        child: Text('Reset Score',
                            style: TextStyle(fontSize: 20.0)),
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }
}
