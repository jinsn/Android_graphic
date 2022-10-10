package com.jsn.demo1

import android.annotation.SuppressLint
import android.content.res.AssetManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.util.Log
import android.view.MotionEvent
import android.view.Surface
import android.view.SurfaceHolder
import android.view.View.GONE
import android.view.View.VISIBLE
import com.jsn.demo1.databinding.ActivityMainBinding
import kotlinx.coroutines.*
import kotlin.concurrent.thread
import kotlin.coroutines.CoroutineContext

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        sv()
        mkDir()
        asset();
        native_create()
        binding.iv.setOnClickListener {
            playPause()
        }
        /*     scope.launch {
                 while(!stop){
                     delay(16)
                     val now =rState()
                         if(now==-1){
                             binding.cb.visibility= GONE
                             binding.iv.visibility= GONE
                         }else if(now ==0){
                             binding.cb.visibility= GONE
                             binding.iv.visibility= GONE
                         }else if(now ==1){
                             binding.cb.text= "running"
                             binding.cb.isChecked=true;
                             binding.cb.visibility= VISIBLE;
                             binding.iv.visibility= VISIBLE
                             binding.iv.setImageResource(R.drawable.aar_ic_pause)
                         }else if(now ==2){
                             binding.cb.text= "pausing"
                             binding.cb.isChecked=false;
                             binding.cb.visibility= VISIBLE
                             binding.iv.visibility= VISIBLE
                             binding.iv.setImageResource(R.drawable.icon_video)

                         }

                 }
             }*/
        t= thread {
            while(!stop){
                Thread.sleep(4)
                val now =rState()
                runOnUiThread {
                    if(now==-1){
                        //binding.cb.visibility= GONE
                        binding.iv.visibility= GONE
                    }else if(now ==0){
                        //binding.cb.visibility= GONE
                        //binding.iv.visibility= GONE
                    }else if(now ==1){
                       // binding.cb.text= "running"
                       // binding.cb.isChecked=true;
                       // binding.cb.visibility= VISIBLE;
                        binding.iv.visibility= VISIBLE
                        binding.iv.setImageResource(R.mipmap.pause_icon)
                    }else if(now ==2){
                       // binding.cb.text= "pausing"
                     //  binding.cb.isChecked=false;
                      //  binding.cb.visibility= VISIBLE
                        binding.iv.visibility= VISIBLE
                        binding.iv.setImageResource(R.mipmap.video_icon)
                    }
                }
            }
        }
    }

    private fun asset() {
        nativeAssetManager(applicationContext.assets)
    }

    private external fun nativeAssetManager(assets: AssetManager)

    val job= SupervisorJob();
    val dispacher= Dispatchers.Main.immediate;
    val context: CoroutineContext =  dispacher+job;
    val scope= CoroutineScope(context);

    fun playPause(){
        native_PlayPause();
    }

    var t:Thread?=null;
    var stop =false;

    private external fun native_create()
    private external fun native_PlayPause()

    @SuppressLint("ClickableViewAccessibility")
    private fun sv() {
        binding.sv.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(p0: SurfaceHolder) {
                native_surface_created(p0.surface)
            }

            override fun surfaceChanged(p0: SurfaceHolder, p1: Int, w: Int, h: Int) {
                native_surface_changed(p0.surface, w, h)
            }

            override fun surfaceDestroyed(p0: SurfaceHolder) {
                native_surface_destroyed(p0.surface)
            }
        })
        binding.sv.setOnTouchListener {_,e: MotionEvent ->

            return@setOnTouchListener false;
        }
    }

    var x=-1 ;
    var y=-1 ;

    override fun onDestroy() {
        super.onDestroy()
        native_destroy()
        job.cancel()
        scope.cancel()
        stop=true
        t?.join()
    }

    override fun onPause() {
        super.onPause()
        native_pause()
    }

    fun mkDir(){
        filesDir.apply {
            absolutePath.also {
                Log.e("imagePath", it );
            }
        }
        getExternalFilesDir(Environment.DIRECTORY_PICTURES).apply {
            this?.also {
                Log.e("imagePath", it.absolutePath );
            }
        }
    }

    external fun rState():Int

    override fun onResume() {
        super.onResume()
        native_resume()
    }

    private external fun native_resume()
    private external fun native_pause()
    private external fun native_destroy()
    private external fun native_surface_created(surface: Surface)
    private external fun native_surface_changed(surface: Surface,w:Int,h:Int)
    private external fun native_surface_destroyed(surface: Surface)




    companion object {
        // Used to load the 'demo1' library on application startup.
        init {
            System.loadLibrary("myapplication")
        }
    }
}

class Jsn(var name:String){
    init {
        name="jsnddd"
        native_construct()
    }

    private  external fun native_construct() ;


    protected fun finalize() {
        native_deconstruct()
    }

    private external fun native_deconstruct()


}