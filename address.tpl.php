<?php

/**
 * @file
 * A template for a postal address.
 */
?>
<address class="contact-info-address" itemprop="address" itemscope="" itemtype="http://schema.org/PostalAddress">
  <?php if ($legal_name): ?>
  <span itemprop="legalName"><?php print $legal_name; ?></span><br />
  <?php endif; ?>
  <span itemprop="streetAddress">
  <?php if ($street_address) {print $street_address . '<br />';} ?>
  <?php if ($street_address_2) {print $street_address_2 . '<br />';} ?>
  </span>
  <?php if ($locality): ?>
  <span itemprop="addressLocality"><?php print $locality; ?></span>, 
  <?php endif; ?>
  <?php if ($region): ?>
  <span itemprop="addressRegion"><?php print $region; ?></span> 
  <?php endif; ?>
  <?php if ($postal_code): ?>
  <span itemprop="postalCode"><?php print $postal_code; ?></span>
  <?php endif; ?>
  <?php if ($country_name): ?>
  <span class="element-invisible" itemprop="addressCountry"><?php print $country_name; ?></span>
  <?php endif; ?>
</address>
