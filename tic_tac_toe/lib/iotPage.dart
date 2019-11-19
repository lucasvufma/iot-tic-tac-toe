import 'package:flutter/material.dart';
import 'package:tic_tac_toe/game.dart';

class IotPage extends StatelessWidget{
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
          Column(
            children: <Widget>[

            Text('Current Requesting To ',style: TextStyle(fontSize: 30.0),),
            Text(iotConnection,style: TextStyle(fontSize: 25.0,color: Colors.red, fontWeight: FontWeight.bold))
            ]),
          TextFormField(
            validator: (value) {
              if (value.isEmpty) {
                return 'Please enter some text';
              }
              return null;
            },
            onSaved: (value)=> _ipAdress=value,
          ),
          Padding(
            padding: const EdgeInsets.symmetric(vertical: 16.0),
            child: RaisedButton(
              padding: const EdgeInsets.all(8.0),
              textColor: Colors.white,
              color: Colors.blue,
              onPressed: () {
                // Validate will return true if the form is valid, or false if
                // the form is invalid.
                if (_formKey.currentState.validate()) {
                  // Process data.
                  _formKey.currentState.save();
                  iotConnection=_ipAdress;
                  print(iotConnection);
                }
                
              },
              child: Text('Submit'),
            ),
  
          ),
        ],
      ),
    );
  }
}


 