package com.fillwave.activity;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;

import com.fillwave.FillwaveView;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 *
 * @see SystemUiHider
 */
public class FillwaveActivity extends Activity {
   
   FillwaveView mView;

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      mView = new FillwaveView(getApplication(), getApplicationInfo().dataDir);
      setContentView(mView);
      copyAssetsToDir(getApplicationInfo().dataDir);
   }

   @Override
   protected void onPause() {
      super.onPause();
      // The following call pauses the rendering thread.
      // If your OpenGL application is memory intensive,
      // you should consider de-allocating objects that
      // consume significant memory here.
      mView.onPause();
   }

   @Override
   protected void onResume() {
      super.onResume();
      // The following call resumes a paused rendering thread.
      // If you de-allocated graphic objects for onPause()
      // this is a good place to re-allocate them.
      mView.onResume();
   }

   private void copyAssetsToDir(String destinationPath) {
       copyFileOrDir("", destinationPath + "/");
   }

   private void copyFileOrDir(String path, String destinationPath) {
        AssetManager assetManager = this.getAssets();
        String assets[] = null;
        try {
            Log.i("tag", "copyFileOrDir() "+path);
            assets = assetManager.list(path);
            if (assets.length == 0) {
                copyFile(path, destinationPath);
            } else {
                String fullPath =  destinationPath + path;
                Log.i("tag", "path="+fullPath);
                File dir = new File(fullPath);
                if (!dir.exists() && !path.startsWith("images") && !path.startsWith("sounds") && !path.startsWith("webkit"))
                    if (!dir.mkdirs())
                        Log.i("tag", "could not create dir " + fullPath);
                for (int i = 0; i < assets.length; ++i) {
                    String p;
                    if (path.equals(""))
                        p = "";
                    else 
                        p = path + "/";

                    if (!path.startsWith("images") && !path.startsWith("sounds") && !path.startsWith("webkit"))
                        copyFileOrDir( p + assets[i], destinationPath);
                }
            }
        } catch (IOException ex) {
            Log.e("tag", "I/O Exception", ex);
        }
    }

    private void copyFile(String filename, String destinationPath) {
        AssetManager assetManager = this.getAssets();

        InputStream in = null;
        OutputStream out = null;
        String newFileName = null;
        try {
            Log.i("tag", "copyFile() "+filename);
            in = assetManager.open(filename);
//            if (filename.endsWith(".jpg")) // extension was added to avoid compression on APK file
//                newFileName = destinationPath + "/" + filename.substring(0, filename.length()-4);
//            else
                newFileName = destinationPath + "/" + filename;
            out = new FileOutputStream(newFileName);

            byte[] buffer = new byte[1024];
            int read;
            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
            in.close();
            in = null;
            out.flush();
            out.close();
            out = null;
        } catch (Exception e) {
            Log.e("tag", "Exception in copyFile() of "+newFileName);
            Log.e("tag", "Exception in copyFile() "+e.toString());
        }

    }
}
