# To Create  Bundle Singel File (Change runtime Platform Version To Current Version In com.github.zakariakov.elforkane.json File).

``` flatpak --user install org.kde.Sdk//5.15-21.08 org.kde.Platform//5.15-21.08  ``` 

``` flatpak-builder --repo=repo --force-clean build-dir com.github.zakariakov.elforkane.json ```

``` flatpak build-bundle repo  com.github.zakariakov.elforkane.flatpak com.github.zakariakov.elforkane  --runtime-repo=https://flathub.org/repo/flathub.flatpakrepo stable ```

``` flatpak install com.github.zakariakov.elforkane.flatpak --user # To Test ```


# To Build and test (Change runtime Platform/Sdk Version To Current Version In com.github.zakariakov.elforkane.json File).

``` flatpak --user install org.kde.Sdk//5.15-21.08 org.kde.Platform//5.15-21.08  ``` 

``` flatpak-builder --user --install --force-clean build-dir com.github.zakariakov.elforkane.json ```

``` flatpak run com.github.zakariakov.elforkane ```
