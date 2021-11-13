# To Install From Bundle (Change runtime Platform Version To Current Version In com.github.zakariakov.elforkane.json File).

''' flatpak --user install org.kde.Platform//5.15-21.08  ''' 

''' wget https://raw.githubusercontent.com/zakariakov/elforkane/master/flatpak_files/com.github.zakariakov.elforkane.flatpak '''

''' flatpak install com.github.zakariakov.elforkane.flatpak --user '''


# To Build and test (Change runtime Platform/Sdk Version To Current Version In com.github.zakariakov.elforkane.json File).

''' flatpak --user install org.kde.Sdk//5.15-21.08 org.kde.Platform//5.15-21.08  ''' 

''' flatpak-builder --user --install --force-clean build-dir com.github.zakariakov.elforkane.json '''

''' flatpak run com.github.zakariakov.elforkane '''
