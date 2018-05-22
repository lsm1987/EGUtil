// Twitter kit 참고

package com.lsm1987.egsnsplugin;

import android.text.TextUtils;
import android.webkit.MimeTypeMap;

import java.io.File;

class EGSnsFileUtils {
    /**
     * @return The MIME type for the given file.
     */
    static String getMimeType(File file) {
        final String ext = getExtension(file.getName());
        if (!TextUtils.isEmpty(ext)) {
            return MimeTypeMap.getSingleton().getMimeTypeFromExtension(ext);
        }
        // default from https://dev.twitter.com/rest/public/uploading-media
        return "application/octet-stream";
    }

    /**
     * @return the extension of the given file name, excluding the dot. For example, "png", "jpg".
     */
    static String getExtension(String filename) {
        if (filename == null) {
            return null;
        }
        final int i = filename.lastIndexOf(".");
        return i < 0 ? "" : filename.substring(i + 1);
    }
}
