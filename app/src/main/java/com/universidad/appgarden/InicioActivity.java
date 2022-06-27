package com.universidad.appgarden;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.universidad.appgarden.fragments.ConfigValvulaFragment;
import com.universidad.appgarden.fragments.MapsValvulasFragment;
import com.universidad.appgarden.fragments.ValvulasFragment;


public class InicioActivity extends AppCompatActivity  {

    private BottomNavigationView mMainNav;
    private FrameLayout mMainFrame;

    private ValvulasFragment valvulasFragment;
    private ConfigValvulaFragment configValvulaFragment;
    private MapsValvulasFragment mapsValvulasFragment;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_inicio);
        //creamos la instancia del objeto BottomNavigationView
        mMainNav = (BottomNavigationView)findViewById(R.id.main_nav);
        mMainFrame = (FrameLayout) findViewById(R.id.main_frame);

        //llamamos las otras clases
        valvulasFragment = new ValvulasFragment();
        configValvulaFragment = new ConfigValvulaFragment();
        mapsValvulasFragment = new MapsValvulasFragment();

        setFragment(valvulasFragment);

        mMainNav.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {

                switch (item.getItemId()){
                    //Obtenemos el ID del boton que seleccionamos y llamamos la clase correspondiente
                    case R.id.valvulas:
                        mMainNav.setItemBackgroundResource(R.color.colorPrimaryDark);
                        setFragment(valvulasFragment);
                        return true;
                    case R.id.config:
                        mMainNav.setItemBackgroundResource(R.color.colorAccent);
                        setFragment(configValvulaFragment);
                        return true;
                    case R.id.mapvalvulas:
                        mMainNav.setItemBackgroundResource(R.color.colorPrimary);
                        setFragment(mapsValvulasFragment);
                        return true;
                    case R.id.masInfo:
                        Intent intent = new Intent(InicioActivity.this, InfoActivity.class);
                        startActivity(intent);
                        return true;
                    default:
                        return false;
                }

                //return false;
            }


        });
    }

    private void setFragment(Fragment fragment) {
        FragmentTransaction fragmentTransaction = getSupportFragmentManager().beginTransaction();
        fragmentTransaction.replace(R.id.main_frame, fragment);
        fragmentTransaction.commit();
    }

}
