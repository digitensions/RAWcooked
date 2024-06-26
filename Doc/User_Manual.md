# RAWcooked User Manual

## Encoding
  
  
```
rawcooked --all <folder> / <file>
```
  
Using the `RAWcooked` tool:  
- encodes an image sequence by supplying the folder path to the sequence, or by supplying the path to a media file within your sequence folder
- encodes with the FFV1 video codec all single-image files or video files in the folder path/folder containing the file
- encodes with the FLAC audio codec all audio files in the folder  
- muxes these into a Matroska container (.mkv)
- uses FFmpeg for this encoding process
  
To encode your sequences using the best preservation flags within RAWcooked then you can use the ```--all``` flag. This flag concatenates several important flags into one ensuring lossless compression and assured reversibilty:  
  
  
| Flags                     | Description                                |
| ------------------------- | ------------------------------------------ |
| ```--info```              | Supplies useful file information           |
| ```--conch```             | Conformance checks file format where supported (partially implemented for DPX) |
| ```--encode```            | Select encode when an image sequence path is supplied  |
| ```--decode```            | Select decode when an FFV1 Matroska file is supplied |
| ```--hash```              | Important flag which computes hashes and embeds them in reversibility data stored in MKV wrapper allowing reversibility test assurance when original sequences absent |
| ```--coherency```         | Ensures package and content are coherent. Eg, sequence gap checks and audio duration matches image sequence duration |
| ```--check```             | Checks that an encoded file can be decoded correctly. If input is raw content, after encoding it checks that output would be same as the input content. Whereas if input is compressed content, it checks that output would be same as the original content where hashes are present |
| ```--check_padding```     | Runs padding checks for DPX files that do not have zero padding. Ensures additional padding data is stored in reversibility file for perfect restoration of the DPX. Can be time consuming  |
| ```--accept-gaps```       | Where gaps in a sequence are found this flag ensures the encoding completes successfully. If you require that gaps are not encoded then follow the ```--all``` command with ```--no-accept-gaps``` |

  
If you do not require all of these flags you can build your own command with just the flags you prefer, for exmaple:
```
rawcooked --info --conch --encode --hash --check --no-accept-gap <folder> / <file>
```
  
For more information about all the available flags in RAWcooked please visit the help page:
```
rawcooked --help / -h
```

  
### For successful encoding

The filenames of the single-image files must end with a numbered sequence. `RAWcooked` will generate the regular expression (regex) to parse in the correct order of all of the frames in the folder. 

The number sequence within the filename can be formed with leading zero padding - e.g. 000001.dpx, 000002.dpx... 500000.dpx - or no leading zero padding - e.g. 1.dpx, 2.dpx... 500000.dpx.

`RAWcooked` has no strict expectations of a complete, continuous number sequence, so breaks in the sequence  - e.g. 47.dpx, 48.dpx, 65.dpx, 66.dpx - will cause no error or failure in `RAWcooked`, unless you specify that you want this with the ```--no-accept-gaps``` flag.

`RAWcooked` has expectations about the folder and subfolder structures containing the image files, and the Matroska that is created will manage subfolders in this way: 
  
- a single folder of image files, or a folder with a single subfolder of image files, will result in a Matroska with one video track
- a folder with multiple subfolders of image files, will result in a Matroska with multiple video tracks, one track per subfolder
  
This behaviour could help to manage different use cases, according to local preference. For example: 
  
- multiple reels in a single Matroska, one track per reel
- multiple film scan attempts (rescanning to address a technical issue in the first scan) in a single Matroska, one track per scan attempt
- multiple overscan approaches (e.g. no perfs, full perfs) in a single Matroska, one track per overscan approach
  
Note that maximum permitted video tracks is encoded in the `RAWcooked` licence (see licence section below), so users may have to request extended track allowance as required.  
  
If your encodings do not succeed and you receive these messages, then you will need to encode your image sequence with the additional flag ```--output-version 2```:
```
Error: the reversibility file is becoming big | Error: undecodable file is becoming too big
```
This is caused by padding data that is not zeros and which must be written into your reversibility data file attachment for restoration to the DPX images when decoded. As this data can exceed FFmpeg's maximum attachment size limit of 1GB, this flag appends the attachment to the FFV1 Matroska file after encoding has completed. This feature is not backward compatible with `RAWcooked` software before version 21.09.

  
## Decoding

```
rawcooked --all <file>
```

The file supplied must be a Matroska container (.mkv) created by the `RAWcooked` software. The `RAWcooked` tool decodes the video, audio and any attachments within the file to its original format.  All metadata accompanying the original data are preserved **bit-by-bit**.

### For successful decoding

For the best decoding experience you should always ensure you encode with the ```--all``` command which includes hashes within the reversibility data of the encoded Matroska file. This ensures that the decoded files can be compared to the original source file hashes, ensuring bit perfect reversibility.
  
  
## Capturing logs
  
It is advisable to always capture the console output of your `RAWcooked` encoding and decoding for review over time. The console output will include `RAWcooked` software information, warning or error messagess, plus confirmation of a successful encode or decode. The console also outputs important encoding information from the FFmpeg encoding software including FFmpeg version, file metadata and stream encoding configurations. Over time this information can be valuable for understanding your compressed files. To capture console log outputs for standard output and standard errors you can use the following commands. You may want to add ```-y``` or ```-n``` which answers yes or no to any questions asked by `RAWcooked` software, unless you're happy monitoring the logs as they are created to intercept any questions.

MacOS/Linux: 
```
rawcooked --all -y <folder path> >> <log path> 2>&1 
```
Windows: 
```
rawcooked --all -y <folder path> 1> <log path> 2>&1 
```
  
## Default licence and expansion

The default `RAWcooked` license allows you to encode and decode without any additional purchases for these flavours:
  
| From                 | To                    |
| -------------------- | --------------------- |
| DPX 8-bit            | FFV1 / Matroska |
| DPX 10-bit LE Filled A | FFV1 / Matroska |
| DPX 10-bit BE Filled A | FFV1 / Matroska |
| PCM 48kHz 16-bit 2 channel in WAV, BWF, RF64, AIFF, AVI | FLAC / Matroska |
  
`RAWcooked` is an open-source project and so the software can be built from binary, but to ensure long-term support and development for this project we ask you install this software using our simple [installation guidelines](https://mediaarea.net/RAWcooked/Download) and support the project by purchasing licence additions to support your file formats, or by sponsorship of new feature development.
  
When you purchase an additional licence you will need to update your software installation with the new licence number, supplied by Media Area.
```
rawcooked --store-license <value>
```
  
To review your licence details you can use this command:
```
rawcooked --show-license
```
  
You may purchase a sublicence from Media Area which can be loaned to third party suppliers for the creation of assets for the purchaser's use. To issue a sublicence that can be loaned to a third party company supplying RAWcooked files to you:  
```
--sublicense <value>
```
The value entry would be your own unique number, and to set a unique expiry date:
```
--sublicense-dur 0
```
This would create a licence that would last until the of the current month. The default value is 1, which would provide an active licence until the end of the following month of issue.  
  
To find out more about licences or any other feature development please contact Media Area - [info@mediaarea.net](mailto:info@mediaarea.net).
