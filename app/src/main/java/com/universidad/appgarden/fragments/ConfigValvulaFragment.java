package com.universidad.appgarden.fragments;


import android.app.TimePickerDialog;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;

import com.universidad.appgarden.R;

import java.io.IOException;
import java.util.Calendar;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

/**
 * A simple {@link Fragment} subclass.
 */
public class ConfigValvulaFragment extends Fragment {

    Spinner listsValvulas;
    EditText tiempoValvula;
    Button btnHora;
    TextView ViewHora;

    CheckBox lunes,martes,miercoles,jueves,viernes,sabado,domingo;
    Button guardarEvento;

    private int hora,minutos;

    String urlcr = "https://addequar.com/valvulas/crear.php";

    public String val;
    public String tiempo;
    public String estado;
    public String dia;
    String horaact;
    String lu="0",ma="0",mi="0",ju="0",vi="0",sa="0",dom="0";
    View vista;


    public ConfigValvulaFragment() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        vista = inflater.inflate(R.layout.fragment_config_valvula, container, false);
        //llamamos el elemento Spinner del activity
        listsValvulas = (Spinner)vista.findViewById(R.id.spinnerListaValvulas);
        //creamos un array con los datos que se van a mostrar en el Spinner
        String [] valvulas ={"Valvula 1","Valvula 2", "Valvula 3","Valvula 4"};
        ArrayAdapter<String> adapter = new ArrayAdapter <String> (getContext(),R.layout.spinner_item_listade_valvulas,valvulas);
        listsValvulas.setAdapter(adapter);

        //obtenemos el item que selecciono el usuario en la lista y lo guardamos el la variable seleccion
        String seleccion = listsValvulas.getSelectedItem().toString();


        //llamamos el elemento EditText del activity
        tiempoValvula = (EditText)vista.findViewById(R.id.editTextTiempoValvulas);



        //llamamos el elemento Button del activity
        btnHora= (Button) vista.findViewById(R.id.buttonHora);
        btnHora.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AsignarHoraEvento();
            }
        });

        //llamamos el elemento TextView del activity en el cual mostraremos la hora selecionada
        ViewHora = (TextView)vista.findViewById(R.id.textViewHora);



        //llamamos todos los CheckBox del activity
        lunes = (CheckBox) vista.findViewById(R.id.checkBoxLunes);
        martes = (CheckBox) vista.findViewById(R.id.checkBoxMartes);
        miercoles = (CheckBox) vista.findViewById(R.id.checkBoxMiercoles);
        jueves = (CheckBox) vista.findViewById(R.id.checkBoxJueves);
        viernes = (CheckBox)vista.findViewById(R.id.checkBoxViernes);
        sabado = (CheckBox) vista.findViewById(R.id.checkBoxSabado);
        domingo = (CheckBox) vista.findViewById(R.id.checkBoxDomingo);

        guardarEvento = (Button) vista.findViewById(R.id.buttonGuardar);
        guardarEvento.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    guardarEvento();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        // Inflate the layout for this fragment
        return vista;
    }






    /************************************************************************
     * **********************************************************************
     ***********************    metodo para seleccionar la hora     *********
     * **********************************************************************
     */
    public void AsignarHoraEvento() {
        final Calendar c = Calendar.getInstance();
        hora=c.get(Calendar.HOUR_OF_DAY);
        minutos=c.get(Calendar.MINUTE);

        TimePickerDialog timePickerDialog = new TimePickerDialog(getContext(), new TimePickerDialog.OnTimeSetListener() {
            @Override
            public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                ViewHora.setText(hourOfDay+": "+minute);
            }
        },hora,minutos,false);
        timePickerDialog.show();
    }


    public void guardarEvento() throws IOException {
        String seleccion = listsValvulas.getSelectedItem().toString();
        //seleccionamos la valvula
        if(seleccion=="Valvula 1"){
            val="1";
        }else if(seleccion=="Valvula 2"){
            val="2";
        }else if(seleccion=="Valvula 3"){
            val="3";
        }else if(seleccion=="Valvula 4"){
            val="4";
        }
        //validamos el dia

        if (lunes.isChecked()==false){
            lu="0";
        }
        else if (lunes.isChecked()==true){
            lu="1";
        }
        if (martes.isChecked()==false){
            ma="0";
        }
        else if (martes.isChecked()==true){
            ma="1";
        }
        if (miercoles.isChecked()==false){
            mi="0";
        }
        else if (miercoles.isChecked()==true){
            mi="1";
        }
        if (jueves.isChecked()==false){
            ju="0";
        }
        else if (jueves.isChecked()==true){
            ju="1";
        }
        if (viernes.isChecked()==false){
            vi="0";
        }
        else if (viernes.isChecked()==true){
            vi="1";
        }
        if (sabado.isChecked()==false){
            sa="0";
        }
        else if (sabado.isChecked()==true){
            sa="1";
        }
        if (domingo.isChecked()==false){
            dom="0";
        }
        else if (domingo.isChecked()==true){
            dom="1";
        }

        horaact = hora+"";
        tiempo=tiempoValvula.getText().toString();
        estado="1";

        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Ok",Toast.LENGTH_LONG);
        toast.show();

    }

    public void RealizarPost(String url) throws IOException {
        MediaType MEDIA_TYPE = MediaType.parse("application/x-www-form-urlencoded");
        OkHttpClient client = new OkHttpClient();
        RequestBody body = RequestBody.create(MEDIA_TYPE, "a=a&v="+val+"&s=1"+"&t="+tiempo+"&d="+lu+"-"+ma+"-"+mi+"-"+ju+"-"+vi+"-"+sa+"-"+dom+"&h="+horaact);
        Request request = new Request.Builder()
                .url(url)
                .post(body)
                .header("Accept", "application/x-www-form-urlencoded")
                .header("Content-Type", "application/x-www-form-urlencoded")
                .build();

        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                String mMessage = e.getMessage().toString();
                Log.w("failure Response", mMessage);
                //call.cancel();
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {

                String mMessage = response.body().string();
                Log.e("Tag",mMessage);
            }
        });
    }

}
