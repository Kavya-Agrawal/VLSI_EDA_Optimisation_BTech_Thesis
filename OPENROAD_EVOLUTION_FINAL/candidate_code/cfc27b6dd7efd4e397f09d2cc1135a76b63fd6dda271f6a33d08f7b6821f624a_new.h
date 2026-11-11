// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02789512;
  double density_weight = 0.36715723;
  double prefix_weight = 0.49105984;
  double neighborhood_weight = 0.09624370;
  double late_weight = 0.28663943;
  double critical_weight = 0.02149084;
  unsigned budget = 24;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
