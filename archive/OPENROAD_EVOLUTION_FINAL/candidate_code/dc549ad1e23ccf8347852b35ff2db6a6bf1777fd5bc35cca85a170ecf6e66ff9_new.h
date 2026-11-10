// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69261049;
  double density_weight = 0.18457770;
  double prefix_weight = 0.10836148;
  double neighborhood_weight = 0.36110492;
  double late_weight = 0.09342057;
  double critical_weight = 0.22756003;
  unsigned budget = 22;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
