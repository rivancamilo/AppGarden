package com.universidad.appgarden.fragments;


        import android.os.Bundle;

        import androidx.fragment.app.Fragment;
        import androidx.fragment.app.FragmentManager;

        import android.view.LayoutInflater;
        import android.view.View;
        import android.view.ViewGroup;

        import com.google.android.gms.maps.CameraUpdateFactory;
        import com.google.android.gms.maps.GoogleMap;
        import com.google.android.gms.maps.OnMapReadyCallback;
        import com.google.android.gms.maps.SupportMapFragment;
        import com.google.android.gms.maps.model.BitmapDescriptorFactory;
        import com.google.android.gms.maps.model.LatLng;
        import com.google.android.gms.maps.model.MarkerOptions;
        import com.universidad.appgarden.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class MapsValvulasFragment extends  SupportMapFragment implements OnMapReadyCallback{
    private GoogleMap mMap;
    View vista;

    public MapsValvulasFragment() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        //vista= inflater.inflate(R.layout.fragment_maps_valvulas, container, false);
        View rootView = super.onCreateView(inflater, container, savedInstanceState);

        getMapAsync(this);

        return rootView;
        //return  vista;
    }

    public void onMapReady(GoogleMap map) {
        // Posicionar el mapa en una localización y con un nivel de zoom
        //valvula 1
        LatLng latLng = new LatLng(4.6097102, -74.081749);
        float zoom = 13;
        map.moveCamera(CameraUpdateFactory.newLatLngZoom(latLng, zoom));

        // Colocar un marcador en la misma posición
        map.addMarker(new MarkerOptions().position(latLng).title("Valvula 1").draggable(true).snippet("Sistema AppGarden").icon(BitmapDescriptorFactory.fromResource(R.drawable.logovalvulamaps)));



        //valvula 2
        LatLng latLng2 = new LatLng(4.6058200, -74.081749);
        map.addMarker(new MarkerOptions().position(latLng2).title("Valvula 2").draggable(true).snippet("Sistema AppGarden").icon(BitmapDescriptorFactory.fromResource(R.drawable.logovalvulamaps)));


        LatLng latLng3 = new LatLng(4.6097102, -74.081749);
        map.addMarker(new MarkerOptions().position(latLng3).title("Valvula 3").draggable(true).snippet("Sistema AppGarden").icon(BitmapDescriptorFactory.fromResource(R.drawable.logovalvulamaps)));



        // Más opciones para el marcador en:
        // https://developers.google.com/maps/documentation/android/marker

        // Otras configuraciones pueden realizarse a través de UiSettings
        // UiSettings settings = getMap().getUiSettings();
    }


}
