package com.universidad.appgarden.fragments;


import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.Switch;
import android.widget.Toast;

import com.universidad.appgarden.R;

import java.io.IOException;
import android.os.Handler;

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
public class ValvulasFragment extends Fragment {

    EditText tiempo_Valvula;//tiempo en que estara abierta la valvula

    Handler h = new Handler();

    Switch valvula1;
    ProgressBar pd,pd2,pd3;
    ImageView valON,valOff;

    Switch valvula2;
    ImageView valON2,valOff2;

    Switch valvula3;
    ImageView valON3,valOff3;

    Switch valvula4;
    ImageView valON4,valOff4;



    String urlcr = "https://addequar.com/valvulas/crear.php";

    public String val;
    public String tiempo;
    public String estado;
    int progress = 0;
    int progress2 = 0;
    int progress3 = 0;
    View vista;

    public ValvulasFragment() {
        // Required empty public constructor
    }

    public void setProgressValue(final int progress) {

        // set the progress
        pd.setProgress(progress);
        // thread is used to change the progress value
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(5500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                setProgressValue(progress + 5);
            }
        });
        thread.start();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        vista = inflater.inflate(R.layout.fragment_valvulas, container, false);


        tiempo_Valvula= (EditText) vista.findViewById(R.id.editTextTiempo);

        //llamamos los elementos del activity Valvula 1
        valvula1 = (Switch) vista.findViewById(R.id.switchValvula1);
        valON = (ImageView) vista.findViewById(R.id.imageViewValvulaON);
        valOff = (ImageView) vista.findViewById(R.id.imageViewValvulaOFF);
        pd = (ProgressBar)vista.findViewById(R.id.progressBar1);
        valvula1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(view.getId()==R.id.switchValvula1){
                    if(valvula1.isChecked()){
                        //la valvula fue encendida
                        try {
                            pd.setVisibility(View.VISIBLE);
                            valOff.setVisibility(View.INVISIBLE);
                            valON.setVisibility(View.VISIBLE);
                            setProgressValue(progress);
                            valvula1ON();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }else{
                        //la valvula fue desactivada
                        try {
                            pd.setVisibility(View.INVISIBLE);
                            valON.setVisibility(View.INVISIBLE);
                            valOff.setVisibility(View.VISIBLE);
                            valvula1OFF();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }

                }


            }
        });

        //***********************   VALVULA 2   ****************************************************

        valvula2 = (Switch) vista.findViewById(R.id.switchValvula2);
        valON2 = (ImageView) vista.findViewById(R.id.imageViewValvulaON2);
        valOff2 = (ImageView) vista.findViewById(R.id.imageViewValvulaOFF2);
        pd2 = (ProgressBar)vista.findViewById(R.id.progressBar2);
        valvula2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(view.getId()==R.id.switchValvula2){
                    if(valvula2.isChecked()){
                        //la valvula fue encendida
                        try {
                            pd2.setVisibility(View.VISIBLE);
                            valOff2.setVisibility(View.INVISIBLE);
                            valON2.setVisibility(View.VISIBLE);
                            setProgressValue(progress2);
                            valvula2ON();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }else{
                        //la valvula fue desactivada
                        try {
                            pd2.setVisibility(View.INVISIBLE);
                            valON2.setVisibility(View.INVISIBLE);
                            valOff2.setVisibility(View.VISIBLE);
                            valvula2OFF();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }

                }


            }
        });

        //***********************   VALVULA 3   ****************************************************

        valvula3 = (Switch) vista.findViewById(R.id.switchValvula3);
        valON3 = (ImageView) vista.findViewById(R.id.imageViewValvulaON3);
        valOff3 = (ImageView) vista.findViewById(R.id.imageViewValvulaOFF3);
        pd3 = (ProgressBar)vista.findViewById(R.id.progressBar3);
        valvula3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(view.getId()==R.id.switchValvula3){
                    if(valvula3.isChecked()){
                        //la valvula fue encendida
                        try {
                            pd3.setVisibility(View.VISIBLE);
                            valOff3.setVisibility(View.INVISIBLE);
                            valON3.setVisibility(View.VISIBLE);
                            valvula3ON();
                            setProgressValue(progress3);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }else{
                        //la valvula fue desactivada
                        try {
                            pd3.setVisibility(View.INVISIBLE);
                            valON3.setVisibility(View.INVISIBLE);
                            valOff3.setVisibility(View.VISIBLE);
                            valvula3OFF();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }

            }
        });

        //***********************   VALVULA 2   ****************************************************

        valvula4 = (Switch) vista.findViewById(R.id.switchValvula4);
        valON4 = (ImageView) vista.findViewById(R.id.imageViewValvulaON4);
        valOff4 = (ImageView) vista.findViewById(R.id.imageViewValvulaOFF4);
        valvula4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(view.getId()==R.id.switchValvula4){
                    if(valvula4.isChecked()){
                        //la valvula fue encendida
                        try {
                            valOff4.setVisibility(View.VISIBLE);
                            //valON4.setVisibility(View.VISIBLE);
                            valvula4ON();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }else{
                        //la valvula fue desactivada
                        try {
                            //valON4.setVisibility(View.INVISIBLE);
                            //valOff4.setVisibility(View.VISIBLE);
                            valvula4OFF();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }

                }


            }
        });


        return vista;
    }





    public void valvula1ON() throws IOException {
        val="1";//Numero de la valvula que vamos ha encender
        //obtenemos el tiempo que el usuario ingreso
        tiempo=tiempo_Valvula.getText().toString();
        estado="1";//prendida

        //funcion que envia los datos usando del metodo POST
        RealizarPost(urlcr);
        //mensaje de respuesta al usuario
        Toast toast = Toast.makeText(getContext(),"Válvula Encendida",Toast.LENGTH_LONG);
        toast.show();
    }
    public void valvula1OFF() throws IOException {
        val="1";
        tiempo=tiempo_Valvula.getText().toString();
        estado="0";//apagada
        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Válvula Apagada",Toast.LENGTH_LONG);
        toast.show();
    }

    //***********************************************************************************************
    public void valvula2ON() throws IOException {
        val="2";
        tiempo=tiempo_Valvula.getText().toString();
        estado="1";

        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Válvula Encendida",Toast.LENGTH_LONG);
        toast.show();
    }
    public void valvula2OFF() throws IOException {
        val="2";
        tiempo=tiempo_Valvula.getText().toString();
        estado="0";
        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Válvula Apagada",Toast.LENGTH_LONG);
        toast.show();
    }


    //************************************************

    public void valvula3ON() throws IOException {
        val="3";
        tiempo=tiempo_Valvula.getText().toString();
        estado="1";

        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Válvula Encendida",Toast.LENGTH_LONG);
        toast.show();
    }
    public void valvula3OFF() throws IOException {
        val="3";
        tiempo=tiempo_Valvula.getText().toString();
        estado="0";
        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Válvula Apagada",Toast.LENGTH_LONG);
        toast.show();
    }

    //*****************************************************************************************************

    public void valvula4ON() throws IOException {
        val="4";
        tiempo=tiempo_Valvula.getText().toString();
        estado="1";
        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Error, Válvula NO Conectada",Toast.LENGTH_LONG);
        toast.show();
    }
    public void valvula4OFF() throws IOException {
        val="4";
        tiempo=tiempo_Valvula.getText().toString();
        estado="0";
        RealizarPost(urlcr);
        Toast toast = Toast.makeText(getContext(),"Error, Válvula NO Conectada",Toast.LENGTH_LONG);
        toast.show();
    }



    public void RealizarPost(String url) throws IOException {
        MediaType MEDIA_TYPE = MediaType.parse("application/x-www-form-urlencoded");
        OkHttpClient client = new OkHttpClient();
        RequestBody body = RequestBody.create(MEDIA_TYPE, "a=m&v="+val+"&s="+estado+"&t="+tiempo+"&d=0&h=13");
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
