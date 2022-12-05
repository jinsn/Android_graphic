package com.jsn.demo1

import android.content.res.AssetManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.MotionEvent
import android.view.Surface
import android.view.SurfaceHolder
import android.view.View
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

        nativeAssetManager(applicationContext.assets)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        sv()
        mkDir()
        native_create()
        binding.iv.setOnClickListener { compoundButton ->
            playPause()
        }
        binding.iv.setOnClickListener {
            playPause()
        }
        t= thread {
            while(!stop){
                Thread.sleep(16)
                val now =rState()
             /*   runOnUiThread {
                    if(now==-1){
                        binding.iv.visibility= GONE
                        binding.iv.visibility= GONE
                    }else if(now ==0){
                        binding.iv.visibility= GONE
                        binding.iv.visibility= GONE
                    }else if(now ==1){
                        binding.iv.visibility= VISIBLE
                        //binding.iv.setImageResource(R.drawable.pause_icon)
                    }else if(now ==2){
                        binding.iv.visibility= VISIBLE
                        //binding.iv.setImageResource(R.drawable.icon_video)
                    }
                }*/
            }
        }
        wasd()
    }


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

    private fun sv() {
        binding.sv.holder.addCallback(object :SurfaceHolder.Callback{
            override fun surfaceCreated(p0: SurfaceHolder) {
                native_surface_created(p0.surface)
            }

            override fun surfaceChanged(p0: SurfaceHolder, p1: Int, w: Int, h: Int) {
                native_surface_changed(p0.surface,w,h)
            }
            override fun surfaceDestroyed(p0: SurfaceHolder) {
                native_surface_destroyed(p0.surface)
            }
        })
        //mouse movement
        binding.sv.setOnTouchListener { view: View, motionEvent: MotionEvent ->
            when(motionEvent.action){

                MotionEvent.ACTION_DOWN->{
                    firstTouch=true
                }
                MotionEvent.ACTION_MOVE->{
                    if(firstTouch){
                        firstTouch=false
                        last_x=motionEvent.x
                        last_y=motionEvent.y
                    }
                    val dx=motionEvent.x-last_x
                    val dy=motionEvent.y-last_y
                    processMouseInput(dx,-dy) //fixme
                    last_x=motionEvent.x
                    last_y=motionEvent.y
                }
                MotionEvent.ACTION_UP->{}
                MotionEvent.ACTION_CANCEL->{}
            }
            true
        }
    }

    private fun processMouseInput(dx: Float, dy: Float) {
        native_mouse_input(dx,dy)
    }

    private external fun native_mouse_input(dx: Float, dy: Float)


    private fun wasd() {
        binding.btW.setOnClickListener {
            native_keyboard_input(-1f,-1f,true,1)
        }
        binding.btA.setOnClickListener {
            native_keyboard_input(-1f,-1f,true,3)
        }
        binding.btS.setOnClickListener {
            native_keyboard_input(-1f,-1f,true,2)
        }
        binding.btD.setOnClickListener {
            native_keyboard_input(-1f,-1f,true,4)
        }
    }
    private external fun native_keyboard_input(dx: Float, dy: Float,keyBoard:Boolean,dir:Int)

    var last_x=0f; var last_y=0f;
    var firstTouch= true;
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

    external fun nativeAssetManager(asset:AssetManager)


    companion object {
        // Used to load the 'demo1' library on application startup.
        init {
            System.loadLibrary("demo1")
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
