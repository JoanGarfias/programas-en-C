#!/usr/bin/env python3
"""
Script para descargar el audio de un video de YouTube y convertirlo a formato WAV.
Requiere las siguientes librerías:
- yt-dlp: para descargar videos de YouTube
- pydub: para conversión de audio
"""

import os
import sys
import argparse
from pathlib import Path
import subprocess
import tempfile

def check_dependencies():
    """Verifica que las dependencias necesarias estén instaladas."""
    try:
        import yt_dlp
        import pydub
        return True
    except ImportError as e:
        print(f"Error: Falta instalar dependencias. {e}")
        print("Instala las dependencias con:")
        print("pip install yt-dlp pydub")
        return False

def download_audio(url, output_dir=".", filename=None):
    """
    Descarga el audio de un video de YouTube.
    
    Args:
        url (str): URL del video de YouTube
        output_dir (str): Directorio de salida
        filename (str): Nombre del archivo (opcional)
    
    Returns:
        str: Ruta del archivo de audio descargado
    """
    import yt_dlp
    
    # Configuración para yt-dlp
    ydl_opts = {
        'format': 'bestaudio/best',  # Mejor calidad de audio disponible
        'outtmpl': os.path.join(output_dir, '%(title)s.%(ext)s'),
        'postprocessors': [{
            'key': 'FFmpegExtractAudio',
            'preferredcodec': 'mp3',
            'preferredquality': '192',
        }],
        'quiet': False,
        'no_warnings': False,
    }
    
    # Si se especifica un nombre de archivo, usarlo
    if filename:
        ydl_opts['outtmpl'] = os.path.join(output_dir, f"{filename}.%(ext)s")
    
    try:
        with yt_dlp.YoutubeDL(ydl_opts) as ydl:
            print(f"Descargando audio de: {url}")
            info = ydl.extract_info(url, download=True)
            
            # Obtener la ruta del archivo descargado
            if filename:
                downloaded_file = os.path.join(output_dir, f"{filename}.mp3")
            else:
                title = info.get('title', 'video')
                # Limpiar el título para usarlo como nombre de archivo
                safe_title = "".join(c for c in title if c.isalnum() or c in (' ', '-', '_')).rstrip()
                downloaded_file = os.path.join(output_dir, f"{safe_title}.mp3")
            
            print(f"Audio descargado como: {downloaded_file}")
            return downloaded_file
            
    except Exception as e:
        print(f"Error al descargar el video: {e}")
        return None

def convert_to_wav(input_file, output_file=None):
    """
    Convierte un archivo de audio a formato WAV.
    
    Args:
        input_file (str): Ruta del archivo de entrada
        output_file (str): Ruta del archivo de salida (opcional)
    
    Returns:
        str: Ruta del archivo WAV generado
    """
    from pydub import AudioSegment
    
    try:
        print(f"Convirtiendo {input_file} a WAV...")
        
        # Cargar el archivo de audio
        audio = AudioSegment.from_file(input_file)
        
        # Si no se especifica archivo de salida, usar el mismo nombre con extensión .wav
        if output_file is None:
            output_file = os.path.splitext(input_file)[0] + '.wav'
        
        # Exportar como WAV
        audio.export(output_file, format='wav')
        
        print(f"Archivo WAV generado: {output_file}")
        return output_file
        
    except Exception as e:
        print(f"Error al convertir a WAV: {e}")
        return None

def main():
    """Función principal del script."""
    parser = argparse.ArgumentParser(
        description='Descarga el audio de un video de YouTube y lo convierte a WAV'
    )
    parser.add_argument('url', help='URL del video de YouTube')
    parser.add_argument('-o', '--output', help='Nombre del archivo de salida (sin extensión)')
    parser.add_argument('-d', '--directory', default='.', help='Directorio de salida (por defecto: actual)')
    parser.add_argument('--keep-mp3', action='store_true', help='Mantener el archivo MP3 original')
    
    args = parser.parse_args()
    
    # Verificar dependencias
    if not check_dependencies():
        sys.exit(1)
    
    # Crear directorio de salida si no existe
    os.makedirs(args.directory, exist_ok=True)
    
    # Descargar el audio
    audio_file = download_audio(args.url, args.directory, args.output)
    
    if audio_file is None:
        print("No se pudo descargar el audio.")
        sys.exit(1)
    
    # Convertir a WAV
    wav_file = convert_to_wav(audio_file)
    
    if wav_file is None:
        print("No se pudo convertir a WAV.")
        sys.exit(1)
    
    # Eliminar el archivo MP3 si no se quiere mantener
    if not args.keep_mp3 and audio_file != wav_file:
        try:
            os.remove(audio_file)
            print(f"Archivo MP3 eliminado: {audio_file}")
        except Exception as e:
            print(f"Advertencia: No se pudo eliminar el archivo MP3: {e}")
    
    print(f"\n¡Proceso completado!")
    print(f"Archivo WAV generado: {wav_file}")

if __name__ == "__main__":
    main() 