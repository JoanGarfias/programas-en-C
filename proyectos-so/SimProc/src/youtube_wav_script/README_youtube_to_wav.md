# YouTube to WAV Converter

Script de Python para descargar el audio de videos de YouTube y convertirlo a formato WAV.

## Características

- Descarga el audio de cualquier video de YouTube
- Convierte automáticamente a formato WAV
- Soporte para personalizar nombres de archivo
- Opción para mantener o eliminar el archivo MP3 intermedio
- Manejo de errores robusto

## Instalación

### 1. Instalar dependencias de Python

```bash
pip install -r requirements.txt
```

O instalar manualmente:

```bash
pip install yt-dlp pydub
```

### 2. Instalar FFmpeg (requerido por pydub)

#### En Ubuntu/Debian:
```bash
sudo apt update
sudo apt install ffmpeg
```

#### En CentOS/RHEL/Fedora:
```bash
sudo dnf install ffmpeg
# o
sudo yum install ffmpeg
```

#### En macOS (con Homebrew):
```bash
brew install ffmpeg
```

#### En Windows:
Descargar desde [https://ffmpeg.org/download.html](https://ffmpeg.org/download.html) y agregar al PATH.

## Uso

### Uso básico:
```bash
python youtube_to_wav.py "https://www.youtube.com/watch?v=VIDEO_ID"
```

### Uso con opciones:
```bash
# Especificar nombre de archivo de salida
python youtube_to_wav.py "https://www.youtube.com/watch?v=VIDEO_ID" -o "mi_audio"

# Especificar directorio de salida
python youtube_to_wav.py "https://www.youtube.com/watch?v=VIDEO_ID" -d "/ruta/destino"

# Mantener el archivo MP3 original
python youtube_to_wav.py "https://www.youtube.com/watch?v=VIDEO_ID" --keep-mp3

# Combinar opciones
python youtube_to_wav.py "https://www.youtube.com/watch?v=VIDEO_ID" -o "mi_audio" -d "/ruta/destino" --keep-mp3
```

### Opciones disponibles:

- `url`: URL del video de YouTube (requerido)
- `-o, --output`: Nombre del archivo de salida (sin extensión)
- `-d, --directory`: Directorio de salida (por defecto: directorio actual)
- `--keep-mp3`: Mantener el archivo MP3 original después de la conversión

## Ejemplos

```bash
# Descargar audio de un video y convertirlo a WAV
python youtube_to_wav.py "https://www.youtube.com/watch?v=dQw4w9WgXcQ"

# Descargar con nombre personalizado
python youtube_to_wav.py "https://www.youtube.com/watch?v=dQw4w9WgXcQ" -o "mi_cancion"

# Descargar en una carpeta específica
python youtube_to_wav.py "https://www.youtube.com/watch?v=dQw4w9WgXcQ" -d "/home/usuario/musica"
```

## Notas importantes

1. **Respeto a los derechos de autor**: Solo descarga contenido que tengas permiso para usar.
2. **Uso personal**: Este script está diseñado para uso personal y educativo.
3. **Calidad**: El script descarga la mejor calidad de audio disponible y la convierte a WAV.
4. **Espacio en disco**: Los archivos WAV son más grandes que los MP3, asegúrate de tener suficiente espacio.

## Solución de problemas

### Error: "No module named 'yt_dlp'"
```bash
pip install yt-dlp
```

### Error: "No module named 'pydub'"
```bash
pip install pydub
```

### Error: "ffmpeg not found"
Instala FFmpeg siguiendo las instrucciones de instalación arriba.

### Error al descargar video
- Verifica que la URL sea válida
- Asegúrate de tener conexión a internet
- Algunos videos pueden tener restricciones de edad o región

## Licencia

Este script es de uso libre para fines educativos y personales. 