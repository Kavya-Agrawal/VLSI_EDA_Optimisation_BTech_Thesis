// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94537791;
  double density_weight = 0.18177006;
  double prefix_weight = 0.36447502;
  double neighborhood_weight = 0.27746838;
  double late_weight = 0.23820670;
  double critical_weight = 0.05766912;
  unsigned budget = 19;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
